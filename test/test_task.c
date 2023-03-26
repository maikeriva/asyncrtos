// https://github.com/ThrowTheSwitch/Unity/blob/master/docs/UnityAssertionsReference.md
#include <test_task_functions.h>
#include <unity.h>
#include <unity_test_runner.h>
#include <test_macros.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TEST_CASE("Task alloc->dealloc", "[aos]")
{
    TEST_HEAP_START
    aos_task_config_t config = {};
    aos_task_t *task1 = aos_task_alloc(&config);
    TEST_ASSERT_NOT_NULL(task1);
    aos_task_free(task1);
    TEST_HEAP_STOP
}

// TEST_CASE("Task alloc with config", "[aos]")
// {
//     TEST_HEAP_START
//     aos_task_config_t config = {
//         .name = "Test task",
//         .stacksize = 2048,
//         .queuesize = 3,
//         .priority = 15};
//     aos_task_t *task1 = aos_task_alloc(&config);
//     TEST_ASSERT_NOT_NULL(task1);
//     aos_task_free(task1);
//     TEST_HEAP_STOP
// }

TEST_CASE("Task alloc->start->stop->dealloc", "[aos]")
{
    TEST_HEAP_START
    aos_task_config_t config = {};
    aos_task_t *task1 = aos_task_alloc(&config);
    TEST_ASSERT_NOT_NULL(task1);

    aos_future_t *start_future = aos_awaitable_alloc(0);
    TEST_ASSERT_NOT_NULL(start_future);
    TEST_ASSERT_TRUE(aos_isresolved(aos_await(aos_task_start(task1, start_future))));
    aos_awaitable_free(start_future);

    aos_future_t *stop_future = aos_awaitable_alloc(0);
    TEST_ASSERT_NOT_NULL(stop_future);
    TEST_ASSERT_TRUE(aos_isresolved(aos_await(aos_task_stop(task1, stop_future))));
    aos_awaitable_free(stop_future);

    vTaskDelay(pdMS_TO_TICKS(1));

    aos_task_free(task1);
    TEST_HEAP_STOP
}

TEST_CASE("Task start and stop hooks", "[aos]")
{
    TEST_HEAP_START
    /**
     * @question:
     * Should onstart and onstop hooks:
     * - Be aos functions? PROBABLY NOT. As we are not supposed to use the task in the start/stop phases, we can wait for their completion synchronously. Nothing prevents us from using aos logic within these sync functions too.
     * - Be specified within the start future? MAYBE. What cases could we have to leverage this possibility? I can't see any at the moment, as the controller task could always take care of doing such stuff itself.
     * - Be changeable at runtime by the controller task? PROBABLY NOT. The task object is meant to be manipulated only by the task itself after creation to avoid race conditions (unlikely if the master->slave pattern is followed, but still). If we badly want this, specifying the hooks in the future is probably a better idea.
     */
    aos_task_config_t config = {
        .onstart = task1_start_hook,
        .onstop = task1_stop_hook,
    };
    aos_task_t *task1 = aos_task_alloc(&config);
    TEST_ASSERT_NOT_NULL(task1);

    aos_future_t *start_future = AOS_AWAITABLE_ALLOC_T(task1_start)();
    TEST_ASSERT_NOT_NULL(start_future);
    TEST_ASSERT_TRUE(aos_isresolved(aos_await(aos_task_start(task1, start_future))));
    aos_awaitable_free(start_future);

    aos_future_t *stop_future = AOS_AWAITABLE_ALLOC_T(task1_stop)();
    TEST_ASSERT_NOT_NULL(stop_future);
    TEST_ASSERT_TRUE(aos_isresolved(aos_await(aos_task_stop(task1, stop_future))));
    aos_awaitable_free(stop_future);

    vTaskDelay(pdMS_TO_TICKS(1));

    aos_task_free(task1);
    TEST_HEAP_STOP
}

TEST_CASE("Task handlers", "[aos]")
{
    TEST_HEAP_START

    aos_task_config_t config = {};
    aos_task_t *task = aos_task_alloc(&config);
    TEST_ASSERT_NOT_NULL(task);
    TEST_ASSERT_EQUAL(0, aos_task_handler_set(task, task1_print0_handler, PRINT0));
    TEST_ASSERT_EQUAL(0, aos_task_handler_set(task, task1_print1_handler, PRINT1));

    aos_future_t *start_future = aos_awaitable_alloc(0);
    TEST_ASSERT_NOT_NULL(start_future);
    TEST_ASSERT_TRUE(aos_isresolved(aos_await(aos_task_start(task, start_future))));
    aos_awaitable_free(start_future);

    aos_future_t *future = AOS_AWAITABLE_ALLOC_T(task1_print0)();
    TEST_ASSERT_NOT_NULL(future);
    TEST_ASSERT_TRUE(aos_isresolved(aos_await(aos_task_send(task, PRINT0, future))));
    aos_awaitable_free(future);

    aos_future_t *future1 = AOS_AWAITABLE_ALLOC_T(task1_print1)(1);
    TEST_ASSERT_NOT_NULL(future1);
    TEST_ASSERT_TRUE(aos_isresolved(aos_await(aos_task_send(task, PRINT1, future1))));
    aos_awaitable_free(future1);

    aos_future_t *stop_future = aos_awaitable_alloc(0);
    TEST_ASSERT_NOT_NULL(stop_future);
    TEST_ASSERT_TRUE(aos_isresolved(aos_await(aos_task_stop(task, stop_future))));
    aos_awaitable_free(stop_future);

    vTaskDelay(pdMS_TO_TICKS(1));

    aos_task_handler_unset(task, PRINT0);
    aos_task_handler_unset(task, PRINT1);

    aos_task_free(task);
    TEST_HEAP_STOP
}

TEST_CASE("Task loops", "[aos]")
{
    TEST_HEAP_START

    aos_task_config_t task_config = {};
    aos_task_t *task1 = aos_task_alloc(&task_config);
    TEST_ASSERT_NOT_NULL(task1);

    aos_task_loop_entry_t *loop0 = aos_task_loop_set(task1, task1_loop0, 100);
    TEST_ASSERT_NOT_NULL(loop0);
    aos_task_loop_entry_t *loop1 = aos_task_loop_set(task1, task1_loop1, 150);
    TEST_ASSERT_NOT_NULL(loop1);

    aos_future_t *start_future = aos_awaitable_alloc(0);
    TEST_ASSERT_NOT_NULL(start_future);
    TEST_ASSERT_TRUE(aos_isresolved(aos_await(aos_task_start(task1, start_future))));
    aos_awaitable_free(start_future);

    // Wait a little
    vTaskDelay(pdMS_TO_TICKS(1000));

    aos_future_t *stop_future = aos_awaitable_alloc(0);
    TEST_ASSERT_NOT_NULL(stop_future);
    TEST_ASSERT_TRUE(aos_isresolved(aos_await(aos_task_stop(task1, stop_future))));
    aos_awaitable_free(stop_future);

    vTaskDelay(pdMS_TO_TICKS(1));

    aos_task_loop_unset(task1, loop0);
    aos_task_loop_unset(task1, loop1);

    aos_task_free(task1);
    TEST_HEAP_STOP
}

// TEST_CASE("Task ipc", "[aos]")
// {
//     TEST_HEAP_START;
//     aos_task_config_t task0_config = {};
//     aos_task_t *task0 = aos_task_alloc(&task0_config);
//     TEST_ASSERT_NOT_NULL(task0);
//     TEST_ASSERT_EQUAL(0, aos_task_handler_set(task1, FORWARD, task_forward_handler));
//     TEST_ASSERT_EQUAL(0, aos_task_handler_set(task1, CALLBACK, task_forward_cb_handler));

//     aos_task_config_t task1_config = {};
//     aos_task_t *task1 = aos_task_alloc(&task1_config);
//     TEST_ASSERT_NOT_NULL(task1);
//     TEST_ASSERT_EQUAL(0, aos_task_handler_set(task1, RESOLVE0, task_resolve0_handler));

//     aos_future_t *start0_future = AOS_AWAITABLE_ALLOC_T(aos_task_start)(task0);
//     TEST_ASSERT_NOT_NULL(start0_future);
//     TEST_ASSERT_EQUAL(AOS_STATE_RESOLVED, aos_await(aos_task_start(start0_future))->state);
//     aos_awaitable_free(start0_future);

//     aos_future_t *start1_future = AOS_AWAITABLE_ALLOC_T(aos_task_start)(task1);
//     TEST_ASSERT_NOT_NULL(start1_future);
//     TEST_ASSERT_EQUAL(AOS_STATE_RESOLVED, aos_await(aos_task_start(start1_future))->state);
//     aos_awaitable_free(start1_future);

//     // Send a message to task0, which will talk to task1, receive a response, and call back to us, all aoshronously
//     aos_future_t *future = AOS_AWAITABLE_ALLOC_T(task_forward)(task1);
//     TEST_ASSERT_NOT_NULL(future);
//     TEST_ASSERT_EQUAL(AOS_STATE_RESOLVED, aos_await(aos_task_send(task0, FORWARD, future)));
//     aos_future_free(future);

//     aos_future_t *stop0_future = AOS_AWAITABLE_ALLOC_T(aos_task_stop)(task0);
//     TEST_ASSERT_NOT_NULL(stop0_future);
//     TEST_ASSERT_EQUAL(AOS_STATE_RESOLVED, aos_await(aos_task_stop(stop0_future)));
//     aos_awaitable_free(stop0_future);
//     aos_task_free(task0);

//     aos_future_t *stop1_future = AOS_AWAITABLE_ALLOC_T(aos_task_stop)(task1);
//     TEST_ASSERT_NOT_NULL(stop1_future);
//     TEST_ASSERT_EQUAL(AOS_STATE_RESOLVED, aos_await(aos_task_stop(stop1_future)));
//     aos_awaitable_free(stop1_future);
//     aos_task_free(task1);
//     TEST_HEAP_STOP;
// }
