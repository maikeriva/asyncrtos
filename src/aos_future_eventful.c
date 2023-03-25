#include <_aos_task.h>
#include <_aos_future.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

typedef struct _aos_eventful_ctx_t
{
    aos_task_t *task;
    AOS_ENUM_T event;
} _aos_eventful_ctx_t;

aos_future_t *aos_eventful_alloc(aos_eventful_config_t *config, size_t args_size)
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
    ctx->task = config->task;
    ctx->event = config->event;
    future->cb = _aos_eventful_cb;
    future->ctx = ctx;
    future->args = args;
    return future;
}

aos_future_t *aos_eventful_free(aos_future_t *future)
{
    if (!future)
        return NULL;

    void *ctx = future->ctx;
    free(future->args);
    free(future);
    return ctx;
}

static void _aos_eventful_cb(aos_future_t *future)
{
    /**
     * NOTE: Taking the semaphore will fail if the task has been dealloated already
     * - Should we enforce a rule in the docs to keep task allocated until all responses are taken care of?
     *   How would the user know that?
     *   User has to ensure that ALL the notifications sent get their responses in the queue before deallocating.
     *   How? In the stop_hook we se sent a request to the underlying tasks to resolve all of them. We wait while they are done.
     */
    xSemaphoreTakeRecursive(((_aos_eventful_ctx_t *)future->ctx)->task->semaphore, portMAX_DELAY);
    _aos_task_msg_t msg = {
        .event = ((_aos_eventful_ctx_t *)future->ctx)->event,
        .future = future};
    xQueueSendToBack(((_aos_eventful_ctx_t *)future->ctx)->task->queue, &msg, portMAX_DELAY);
    xSemaphoreGiveRecursive(((_aos_eventful_ctx_t *)future->ctx)->task->semaphore);
}
