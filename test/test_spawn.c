// https://github.com/ThrowTheSwitch/Unity/blob/master/docs/UnityAssertionsReference.md
#include <test_functions.h>
#include <unity.h>
#include <unity_test_runner.h>
#include <test_macros.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static void test_spawn_wrapper(aos_future_t *future)
{
    test_fn_resolve_0(future);
}

TEST_CASE("Spawn", "[aos]")
{
    TEST_HEAP_START

    aos_spawn_config_t config = {};
    aos_future_t *future = AOS_AWAITABLE_ALLOC_T(test_fn_resolve_0)();
    TEST_ASSERT_NOT_NULL(future);
    aos_spawn(&config, test_spawn_wrapper, future);
    TEST_ASSERT_TRUE(aos_isresolved(aos_await(future)));
    aos_awaitable_free(future);

    vTaskDelay(pdMS_TO_TICKS(1));
    TEST_HEAP_STOP
}
