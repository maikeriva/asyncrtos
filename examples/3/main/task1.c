#include <stdio.h>
#include <aos.h>

static aos_task_t *_task1 = NULL;

enum
{
    TASK1_SAYHELLO
};
void task1_handler_sayhello(aos_task_t *task, aos_future_t *future)
{
    printf("Task1: Hello!\n");
    aos_resolve(future);
}

AOS_DEFINE(task1_sayhello)
aos_future_t *task1_sayhello(aos_future_t *future) {
    return aos_task_send(_task1,TASK1_SAYHELLO,future);
}

void task1_init() {
    aos_task_config_t config1 = {};
    _task1 = aos_task_alloc(&config1);
    aos_task_handler_set(_task1, task1_handler_sayhello, TASK1_SAYHELLO);
    aos_future_t *start1_future = aos_awaitable_alloc(0);
    aos_await(aos_task_start(_task1, start1_future));
    aos_awaitable_free(start1_future);
}
