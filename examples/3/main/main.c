/**
 * @file main.c
 * @author Michele Riva (micheleriva@protonmail.com)
 * @brief AsyncRTOS example 3
 * @version 0.1
 * @date 2023-04-17
 *
 * @copyright Copyright (c) 2023
 *
 * This example is equivalent to example 2, but it structures the code properly by moving the implementation of each task to its own files.
 * Notice how each task only exposes its own API. This is the recommended way to structure AsyncRTOS applications.
 */
#include <aos.h>
#include "task0.h"
#include "task1.h"

void app_main(void)
{
    // Init tasks
    task0_init();
    task1_init();

    // Send a DOSOMETHING message to task0
    aos_future_t *dosomething_future = AOS_AWAITABLE_ALLOC_T(task0_dosomething)();
    aos_await(task0_dosomething(dosomething_future));
    aos_awaitable_free(dosomething_future);
}
