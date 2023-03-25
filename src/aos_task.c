#include <_aos_task.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
// #include <string.h>

typedef struct _aos_task_handler_entry_t
{
    aos_task_handler_t handler;
    AOS_ENUM_T event;
    _aos_task_handler_entry_t *next;
} _aos_task_handler_entry_t;

typedef struct _aos_task_loop_entry_t
{
    aos_task_loop_t loop;
    unsigned int interval;
    unsigned int last_exec;
    _aos_task_loop_entry_t *next;
} _aos_task_loop_entry_t;

typedef enum
{
    AOS_TASK_EVENT_START = AOS_ENUM_MIN,
    AOS_TASK_EVENT_STOP,
    AOS_TASK_EVENT_LOOPREGISTER,
    AOS_TASK_EVENT_LOOPUNREGISTER,
} _aos_task_event_t;

struct _aos_task_t
{
    unsigned int stacksize;
    unsigned int queuesize;
    unsigned int priority;
    SemaphoreHandle_t semaphore;
    QueueHandle_t queue;
    TaskHandle_t task;
    char *name;
    void *args;
    aos_task_onstart_fn_t onstart;
    aos_task_onstop_fn_t onstop;
    _aos_task_handler_entry_t *handlers;
    _aos_task_loop_entry_t *loops;
};

typedef struct _aos_eventful_ctx_t
{
    aos_task_t *task;
    AOS_ENUM_T event;
} _aos_eventful_ctx_t;

aos_task_t *aos_task_alloc(aos_task_config_t *config)
{
    aos_task_t *task = calloc(1, sizeof(aos_task_t));
    SemaphoreHandle_t semaphore = xSemaphoreCreateRecursiveMutex();
    char *name = config->name ? strdup(config->name) : NULL;
    if (!task || !semaphore || (config->name && !name))
    {
        free(task);
        vSemaphoreDelete(semaphore);
        free(name);
        return NULL;
    }
    task->semaphore = semaphore;
    task->name = name; // FIXME: Verify this can be null
    task->stacksize = config->stacksize ? config->stacksize : AOS_TASK_STACKSIZEDEFAULT;
    task->queuesize = config->queuesize ? config->queuesize : AOS_TASK_QUEUESIZEDEFAULT;
    task->priority = config->priority ? config->priority : AOS_TASK_PRIORITYDEFAULT;
    task->args = config->args;
    return task;
}

void aos_task_free(aos_task_t *task)
{
    if (!task)
        return;
    vSemaphoreDelete(task->semaphore);
    _aos_task_handler_entry_t *handler = task->handlers;
    while (handler)
    {
        _aos_task_handler_entry_t *next_handler = handler->next;
        free(handler);
        handler = next_handler;
    }
    _aos_task_loop_entry_t *loop = task->loops;
    while (loop)
    {
        _aos_task_loop_entry_t *next_loop = loop->next;
        free(loop);
        loop = next_loop;
    }
    free(task->name);
    free(task);
}

aos_future_t *aos_task_start(aos_task_t *task, aos_future_t *future)
{
    if (task->queue)
    {
        aos_reject(future);
        return future;
    }
    task->queue = xQueueCreate(task->queuesize, sizeof(_aos_task_msg_t));
    if (!task->queue)
    {
        aos_reject(future);
        return future;
    }
    if (!xTaskCreate(
            _aos_task,
            task->name,
            task->stacksize,
            task,
            task->priority,
            &task->task))
    {
        vQueueDelete(task->queue);
        task->queue = NULL;
        aos_reject(future);
        return future;
    }
    return aos_task_send(task, AOS_TASK_EVENT_START, future);
}

aos_future_t *aos_task_stop(aos_task_t *task, aos_future_t *future)
{
    return aos_task_send(task, AOS_TASK_EVENT_STOP, future);
}

aos_future_t *aos_task_send(aos_task_t *task, AOS_ENUM_T event, aos_future_t *future)
{
    xSemaphoreTakeRecursive(task->semaphore, portMAX_DELAY);
    if (!task->queue)
    {
        xSemaphoreGiveRecursive(task->semaphore);
        aos_reject(future);
        return future;
    }
    _aos_task_msg_t msg = {
        .event = event,
        .future = future};
    if (!xQueueSendToBack(task->queue, &msg, portMAX_DELAY))
    {
        xSemaphoreGiveRecursive(task->semaphore);
        aos_reject(future);
        return future;
    }
    xSemaphoreGiveRecursive(task->semaphore);
    return future;
}

aos_future_t *aos_eventful_alloc(aos_future_t *prev_future, aos_task_t *task, AOS_ENUM_T event, size_t args_size)
{
    aos_future_t *future = calloc(1, sizeof(aos_future_t));
    _aos_eventful_ctx_t *ctx = calloc(1, sizeof(_aos_eventful_ctx_t));
    void *args = args_size ? calloc(1, args_size) : NULL;
    if (!future || !ctx || (args_size && !args))
    {
        free(future);
        free(ctx);
        free(args);
        return NULL;
    }
    ctx->task = task;
    ctx->event = event;
    future->cb = _aos_eventful_cb;
    future->ctx = ctx;
    future->args = args;
    return future;
}

aos_future_t *aos_eventful_free(aos_future_t *future)
{
    if (!future)
        return NULL;

    aos_future_t *prev = future->prev;
    free(future->ctx);
    free(future->args);
    free(future);
    return prev;
}

void *aos_task_args_get(aos_task_t *task)
{
    return task->args;
}

static void _aos_task(void *args)
{
    aos_task_t *task = args;
    _aos_task_msg_t msg = {};
    while (true)
    {
        if (pdTRUE == xQueueReceive(task->queue, &msg, _aos_task_delay_get(task)))
        {
            if (msg.event == AOS_TASK_EVENT_START)
            {
                if (task->onstart)
                {
                    if (task->onstart(task, msg.future))
                    {
                        _aos_task_queue_close(task);
                        vTaskDelete(NULL);
                    }
                }
                else
                {
                    aos_resolve(msg.future);
                }
            }
            else if (msg.event == AOS_TASK_EVENT_STOP)
            {
                if (task->onstop)
                {
                    if (task->onstop(task, msg.future))
                    {
                        _aos_task_queue_close(task);
                        vTaskDelete(NULL);
                    }
                }
                else
                {
                    _aos_task_queue_close(task);
                    aos_resolve(msg.future);
                    vTaskDelete(NULL);
                }
            }
            else
            {
                for (_aos_task_handler_entry_t *entry = task->handlers; entry; entry = entry->next)
                {
                    if (entry->event == msg.event)
                    {
                        entry->handler(task, msg.future);
                        break;
                    }
                }
            }
        }
        else
        {
            TickType_t tick = xTaskGetTickCount();
            for (_aos_task_loop_entry_t *entry = task->loops; entry; entry = entry->next)
            {
                if (tick - entry->last_exec >= entry->interval)
                {
                    entry->last_exec = tick;
                    entry->loop(task);
                }
            }
        }
    }
}

unsigned int aos_task_handler_set(aos_task_t *task, aos_task_handler_t handler, AOS_ENUM_T event)
{
    _aos_task_handler_entry_t **entry = &task->handlers;
    while (*entry)
    {
        if ((*entry)->event == event)
        {
            (*entry)->handler = handler;
            return 0;
        }
        entry = &(*entry)->next;
    }
    *entry = calloc(1, sizeof(_aos_task_handler_entry_t));
    if (!*entry)
    {
        return NULL;
    }
    (*entry)->handler = handler;
    (*entry)->event = event;
    return 0;
}

void aos_task_handler_unset(aos_task_t *task, AOS_ENUM_T event)
{
    for (_aos_task_handler_entry_t **entry = &task->handlers; *entry; entry = (*entry)->next ? &(*entry)->next : NULL)
    {
        if ((*entry)->event == event)
        {
            _aos_task_handler_entry_t *entry_next = (*entry)->next;
            free(*entry);
            *entry = entry_next;
            return;
        }
    }
}

aos_task_loop_entry_t *aos_task_loop_set(aos_task_t *task, aos_task_loop_t loop, unsigned int interval_ms)
{
    _aos_task_loop_entry_t **entry = &task->loops;
    while (*entry)
    {
        entry = &(*entry)->next;
    }
    *entry = calloc(1, sizeof(_aos_task_loop_entry_t));
    if (!*entry)
    {
        return NULL;
    }
    (*entry)->loop = loop;
    (*entry)->interval = pdMS_TO_TICKS(interval_ms);
    return *entry;
}

void aos_task_loop_unset(aos_task_t *task, aos_task_loop_entry_t *loop_entry)
{
    for (_aos_task_loop_entry_t **entry = &task->loops; *entry; entry = (*entry)->next ? &(*entry)->next : NULL)
    {
        if ((*entry) == loop_entry)
        {
            _aos_task_loop_entry_t *entry_next = (*entry)->next;
            free(*entry);
            *entry = entry_next;
            return;
        }
    }
}

bool aos_task_isstopping(aos_task_t *task)
{
    return task->queue == NULL;
}

static void _aos_task_queue_close(aos_task_t *task)
{
    xSemaphoreTakeRecursive(task->semaphore, portMAX_DELAY);
    QueueHandle_t queue = task->queue;
    task->queue = NULL;
    _aos_task_msg_t next_msg = {};
    while (pdTRUE == xQueueReceive(queue, &next_msg, 0))
    {
        if (aos_isresolved(next_msg.future))
        {
            // It is a response! Call its handler so that it can deallocate accordingly.
            for (_aos_task_handler_entry_t *entry = task->handlers; entry; entry = entry->next)
            {
                if (entry->event == msg.event)
                {
                    entry->handler(task, msg.future);
                    break;
                }
            }
            // It is a notifier response! Use alternative free method.
            // _aos_eventful_ctx_free(next_msg.future); // Private function?
            // aos_eventful_free(next_msg.future); // Returns context?
        }
        else
        {
            aos_reject(next_msg.future);
        }
    }
    vQueueDelete(queue);
    xSemaphoreGiveRecursive(task->semaphore);
}

static TickType_t _aos_task_delay_get(aos_task_t *task)
{
    TickType_t wait_ticks = portMAX_DELAY;
    TickType_t tick = xTaskGetTickCount();
    for (_aos_task_loop_entry_t *loop_entry = task->loops; loop_entry; loop_entry = loop_entry->next)
    {
        TickType_t elapsed = tick - loop_entry->last_exec;
        TickType_t ticks_to_next_exec = loop_entry->interval < elapsed ? 0 : loop_entry->interval - elapsed;
        if (ticks_to_next_exec < wait_ticks)
            wait_ticks = ticks_to_next_exec;
        // printf("tick:%u last_exec:%u interval:%u ticks_to_next_exec:%u wait_ticks:%u\n", tick, loop_entry->last_exec, loop_entry->interval, ticks_to_next_exec, wait_ticks);
    }
    return wait_ticks;
}
