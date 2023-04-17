/**
 * @file main.c
 * @author Michele Riva (micheleriva@protonmail.com)
 * @brief AsyncRTOS example 2
 * @version 0.1
 * @date 2023-04-17
 *
 * @copyright Copyright (c) 2023
 *
 * This example shows asynchronous communication between tasks, as well as a "passthrough" scenario.
 * Here's what happens, step-by-step:
 * - The main task initializes and starts task0 and task1, then sends a DOSOMETHING message to task0 and awaits the result synchronously.
 * - Task0 receives the message and calls the "DOSOMETHING" handler, which sends a new "SAYHELLO" message to task1. Notice that it does so using an eventful future, for a couple of reasons:
 *   1. An eventful future will callback the task with another message (in this case "DOSOMETHING_CB") when the future will be resolved. This allows the task to still be responsive to incoming messages.
 *   2. The eventful future allows to attach a context to it, in this case the future coming from the main task. This way, the task doesn't need to keep track of it as it can be retrieved in the "DOSOMETHING_CB" handler when freeing up the eventful future. This technique is referred to as "passthrough".
 * - Task1 receives the "SAYHELLO" message, prints "Hello!" to screen, and resolves the future. This will implicitly send a "DOSOMETHING_CB" message to task0, yet notice how task0 has no idea about that. To the handler, all futures are the same thus no custom logic is needed to handle different types.
 * - Task0 receives the "DOSOMETHING_CB" message, frees the future, retrieves the parent future in the process, and resolves it.
 * - The main task is unlocked.
 *
 */
#include <stdio.h>
#include <aos.h>
#include <sdkconfig.h>

static aos_task_t *_task0 = NULL;
static aos_task_t *_task1 = NULL;

// Task 1 handlers
enum
{
    TASK1_SAYHELLO
};
AOS_DECLARE(main_task1_handler_sayhello)
AOS_DEFINE(main_task1_handler_sayhello)
void main_task1_handler_sayhello(aos_task_t *task, aos_future_t *future)
{
    printf("Task1: Hello!\n");
    aos_resolve(future);
}

// Task 0 handlers
enum
{
    TASK0_DOSOMETHING,
    TASK0_DOSOMETHING_CB
};
AOS_DECLARE(main_task0_handler_dosomething)
AOS_DEFINE(main_task0_handler_dosomething)
void main_task0_handler_dosomething(aos_task_t *task, aos_future_t *future)
{
    aos_eventful_config_t new_config = {
        .ctx = future,
        .event = TASK0_DOSOMETHING_CB,
        .task = task};
    aos_future_t *new_future = AOS_EVENTFUL_ALLOC_T(main_task1_handler_sayhello)(&new_config);
    aos_task_send(_task1, TASK1_SAYHELLO, new_future);
}
void main_task0_handler_dosomething_cb(aos_task_t *task, aos_future_t *future)
{
    aos_future_t *parent_future = aos_eventful_free(future);
    aos_resolve(parent_future);
}

void app_main(void)
{
    // Create first task and set handlers
    aos_task_config_t config0 = {};
    _task0 = aos_task_alloc(&config0);
    aos_task_handler_set(_task0, main_task0_handler_dosomething, TASK0_DOSOMETHING);
    aos_task_handler_set(_task0, main_task0_handler_dosomething_cb, TASK0_DOSOMETHING_CB);

    // Create second task and set handlers
    aos_task_config_t config1 = {};
    _task1 = aos_task_alloc(&config1);
    aos_task_handler_set(_task0, main_task1_handler_sayhello, TASK1_SAYHELLO);

    // Start tasks
    aos_future_t *start0_future = aos_awaitable_alloc(0);
    aos_await(aos_task_start(_task0, start0_future));
    aos_awaitable_free(start0_future);
    aos_future_t *start1_future = aos_awaitable_alloc(0);
    aos_await(aos_task_start(_task1, start1_future));
    aos_awaitable_free(start1_future);

    // Send a DOSOMETHING message to task0
    aos_future_t *dosomething_future = AOS_AWAITABLE_ALLOC_T(main_task0_handler_dosomething)();
    aos_await(aos_task_send(_task0, TASK0_DOSOMETHING, dosomething_future));
    aos_awaitable_free(dosomething_future);
}
