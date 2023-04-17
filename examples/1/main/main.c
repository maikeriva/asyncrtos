/**
 * @file main.c
 * @author Michele Riva (micheleriva@protonmail.com)
 * @brief AsyncRTOS example 1
 * @version 0.1
 * @date 2023-04-17
 * 
 * @copyright Copyright (c) 2023
 * 
 * This example is very similar to example 0, but also shows:
 * - How to define handlers which accept parameters through decorators
 * - How to send messages with parameters to tasks
 * 
 */
#include <stdio.h> 
#include <aos.h>
#include <sdkconfig.h>

enum
{
    DOSOMETHING
};

AOS_DECLARE(main_task_handler_dosomething, int arg1)
AOS_DEFINE(main_task_handler_dosomething, int)
void main_task_handler_dosomething(aos_task_t *task, aos_future_t *future)
{
    AOS_ARGS_T(main_task_handler_dosomething) *args = aos_args_get(future);
    printf("Task: I am doing something (arg1:%d)\n", args->arg1);
    aos_resolve(future);
}

void app_main(void)
{
    // Create a task
    aos_task_config_t config = {};
    aos_task_t *task = aos_task_alloc(&config);

    // Register task handler
    aos_task_handler_set(task, main_task_handler_dosomething, DOSOMETHING);

    // Start task
    aos_future_t *start_future = aos_awaitable_alloc(0);
    aos_await(aos_task_start(task, start_future));
    aos_awaitable_free(start_future);

    // Send a DOSOMETHING message
    aos_future_t *dosomething_future = AOS_AWAITABLE_ALLOC_T(main_task_handler_dosomething)(1);
    aos_await(aos_task_send(task, DOSOMETHING, dosomething_future));
    aos_awaitable_free(dosomething_future);
}
