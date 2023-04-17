#include <aos.h>
#include "task1.h"

static aos_task_t *_task0 = NULL;

enum
{
    TASK0_DOSOMETHING,
    TASK0_DOSOMETHING_CB
};
static void task0_handler_dosomething(aos_task_t *task, aos_future_t *future)
{
    aos_eventful_config_t new_config = {
        .ctx = future,
        .event = TASK0_DOSOMETHING_CB,
        .task = task};
    aos_future_t *new_future = AOS_EVENTFUL_ALLOC_T(task1_sayhello)(&new_config);
    task1_sayhello(new_future);
}
static void task0_handler_dosomething_cb(aos_task_t *task, aos_future_t *future)
{
    aos_future_t *parent_future = aos_eventful_free(future);
    aos_resolve(parent_future);
}

AOS_DEFINE(task0_dosomething)
aos_future_t *task0_dosomething(aos_future_t *future)
{
    return aos_task_send(_task0, TASK0_DOSOMETHING, future);
}

void task0_init()
{
    aos_task_config_t config0 = {};
    _task0 = aos_task_alloc(&config0);
    aos_task_handler_set(_task0, task0_handler_dosomething, TASK0_DOSOMETHING);
    aos_task_handler_set(_task0, task0_handler_dosomething_cb, TASK0_DOSOMETHING_CB);
    aos_future_t *start0_future = aos_awaitable_alloc(0);
    aos_await(aos_task_start(_task0, start0_future));
    aos_awaitable_free(start0_future);
}
