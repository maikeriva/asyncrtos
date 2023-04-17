// https://github.com/ThrowTheSwitch/Unity/blob/master/docs/UnityAssertionsReference.md
#include <test_task_functions.h>
#include <stdio.h>
#include <unity.h>

AOS_DEFINE(task_print0)
void task_print0_handler(aos_task_t *task, aos_future_t *future)
{
    // AOS_ARGS_T(task_print0) *args = aos_args_get(future);
    printf("print0\n");
    aos_resolve(future);
}

AOS_DEFINE(task_print1, int)
void task_print1_handler(aos_task_t *task, aos_future_t *future)
{
    AOS_ARGS_T(task_print1) *args = aos_args_get(future);
    printf("print1: arg1=%d\n", args->arg1);
    aos_resolve(future);
}

AOS_DEFINE(task_forward, aos_task_t *)
void task_forward_handler(aos_task_t *task, aos_future_t *future)
{
    AOS_ARGS_T(task_forward) *args = aos_args_get(future);

    printf("forward\n");
    aos_eventful_config_t config = {
        .event = FORWARDCB,
        .task = task,
        .ctx = future};
    aos_future_t *new_future = AOS_EVENTFUL_ALLOC_T(task_print1)(&config, 1);
    TEST_ASSERT_NOT_NULL(new_future);
    aos_task_send(args->task, PRINT1, new_future);
}

void task_forward_cb_handler(aos_task_t *task, aos_future_t *future)
{
    printf("forward_cb\n");
    TEST_ASSERT_TRUE(aos_isresolved(future));
    aos_future_t *old_future = aos_eventful_free(future);
    TEST_ASSERT_NOT_NULL(old_future);
    aos_resolve(old_future);
}

AOS_DEFINE(task_start)
unsigned int task_start_hook(aos_task_t *task, aos_future_t *future)
{
    printf("start_hook\n");
    aos_resolve(future);
    return 0;
}

AOS_DEFINE(task_stop)
unsigned int task_stop_hook(aos_task_t *task, aos_future_t *future)
{
    printf("stop_hook\n");
    aos_resolve(future);
    return 0;
}

void task_loop0(aos_task_t *task)
{
    printf("loop0\n");
}

void task_loop1(aos_task_t *task)
{
    printf("loop1\n");
}