/**
 * @file main.c
 * @author Michele Riva (micheleriva@protonmail.com)
 * @brief AsyncRTOS example 0
 * @version 0.1
 * @date 2023-04-17
 * 
 * @copyright Copyright (c) 2023
 * 
 * This basic example shows:
 * - How to create a basic asynchronous task and register a handler to it
 * - How to start the task synchronously with an awaitable future
 * - How to send a message to the task synchronously with an awaitable future
 * 
 */
#include <stdio.h>
#include <aos.h>
#include <sdkconfig.h>

enum
{
    DOSOMETHING
};
void main_task_handler_dosomething(aos_task_t *task, aos_future_t *future)
{
    printf("Task: I am doing something\n");
    aos_resolve(future);
}

void app_main(void)
{
    // Create a task
    aos_task_config_t config = {};
    aos_task_t *task = aos_task_alloc(&config);

    // Register task handler for the DOSOMETHING event
    aos_task_handler_set(task, main_task_handler_dosomething, DOSOMETHING);

    // Start task
    aos_future_t *start_future = aos_awaitable_alloc(0);
    aos_await(aos_task_start(task, start_future));
    aos_awaitable_free(start_future);

    // Send a DOSOMETHING message
    aos_future_t *dosomething_future = aos_awaitable_alloc(0);
    aos_await(aos_task_send(task, DOSOMETHING, dosomething_future));
    aos_awaitable_free(dosomething_future);
}
