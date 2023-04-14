// https://github.com/ThrowTheSwitch/Unity/blob/master/docs/UnityAssertionsReference.md
#include <test_functions.h>
#include <unity.h>
#include <unity_test_runner.h>
#include <test_macros.h>

TEST_CASE("Resolve forgettable 0", "[aos]")
{
    TEST_HEAP_START
    aos_future_t *future = AOS_FORGETTABLE_ALLOC_T(test_fn_resolve_0)();
    TEST_ASSERT_NOT_NULL(future);
    test_fn_resolve_0(future);
    TEST_HEAP_STOP
}

TEST_CASE("Resolve forgettable 1", "[aos]")
{
    TEST_HEAP_START
    aos_future_t *future = AOS_FORGETTABLE_ALLOC_T(test_fn_resolve_1)(1);
    TEST_ASSERT_NOT_NULL(future);
    test_fn_resolve_1(future);
    TEST_HEAP_STOP
}
