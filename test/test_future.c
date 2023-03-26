// https://github.com/ThrowTheSwitch/Unity/blob/master/docs/UnityAssertionsReference.md
#include <test_functions.h>
#include <unity.h>
#include <unity_test_runner.h>
#include <test_macros.h>

struct test_cb_ctx_t {
    int m1;
};

static void test_cb(aos_future_t *future)
{
    struct test_cb_ctx_t *ctx = aos_future_free(future);
    TEST_ASSERT_NOT_NULL(ctx);
    printf("m1:%d",ctx->m1);
    free(ctx);
    TEST_HEAP_STOP
}

TEST_CASE("Resolve callbacker 0, sweetened with allocator_t", "[aos]")
{
    TEST_HEAP_START
    struct test_cb_ctx_t *ctx = calloc(1,sizeof(struct test_cb_ctx_t));
    TEST_ASSERT_NOT_NULL(ctx);
    aos_future_config_t config = {
        .cb = test_cb,
        .ctx = ctx
    };
    aos_future_t *future = AOS_FUTURE_ALLOC_T(test_fn_resolve_0)(&config);
    TEST_ASSERT_NOT_NULL(future);
    test_fn_resolve_0(future);
}
