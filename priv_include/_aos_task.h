#include <aos_task.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

typedef struct _aos_task_handler_entry_t _aos_task_handler_entry_t;
struct _aos_task_handler_entry_t
{
    aos_task_handler_t handler;
    AOS_ENUM_T event;
    _aos_task_handler_entry_t *next;
};

typedef struct _aos_task_loop_entry_t _aos_task_loop_entry_t;
struct _aos_task_loop_entry_t
{
    aos_task_loop_t loop;
    unsigned int interval;
    unsigned int last_exec;
    _aos_task_loop_entry_t *next;
};

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
    aos_task_hook_t onstart;
    aos_task_hook_t onstop;
    _aos_task_handler_entry_t *handlers;
    _aos_task_loop_entry_t *loops;
};

typedef struct _aos_task_msg_t
{
    AOS_ENUM_T event;
    aos_future_t *future;
} _aos_task_msg_t;
