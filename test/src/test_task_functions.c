// https://github.com/ThrowTheSwitch/Unity/blob/master/docs/UnityAssertionsReference.md
#include <test_task_functions.h>
#include <stdio.h>

AOS_DEFINE(task1_print0)
void task1_print0_handler(aos_task_t *task, aos_future_t *future)
{
    // AOS_ARGS_T(task1_print0) *args = aos_args_get(future);
    printf("print0\n");
    aos_resolve(future);
}

AOS_DEFINE(task1_print1, int)
void task1_print1_handler(aos_task_t *task, aos_future_t *future)
{
    AOS_ARGS_T(task1_print1) *args = aos_args_get(future);
    printf("print0: arg1=%d\n", args->arg1);
    aos_resolve(future);
}

AOS_DEFINE(task1_start)
unsigned int task1_start_hook(aos_task_t *task, aos_future_t *future)
{
    printf("Task1 is starting");
    aos_resolve(future);
    return 0;
}

AOS_DEFINE(task1_stop)
unsigned int task1_stop_hook(aos_task_t *task, aos_future_t *future)
{
    printf("Task1 is stopping");
    aos_resolve(future);
    return 0;
}

void task1_loop0(aos_task_t *task)
{
    printf("Loop0\n");
}

void task1_loop1(aos_task_t *task)
{
    printf("Loop1\n");
}