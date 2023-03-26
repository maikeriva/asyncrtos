// https://github.com/ThrowTheSwitch/Unity/blob/master/docs/UnityAssertionsReference.md
#include <test_functions.h>
#include <stdio.h>

AOS_DEFINE(test_fn_resolve_0)
aos_future_t *test_fn_resolve_0(aos_future_t *future)
{
    printf("no_args\n");
    aos_resolve(future);
    return future;
}

AOS_DEFINE(test_fn_resolve_1, int)
aos_future_t *test_fn_resolve_1(aos_future_t *future)
{
    AOS_ARGS_T(test_fn_resolve_1) *args = aos_args_get(future);
    printf("arg1:%d\n", args->arg1);
    aos_resolve(future);
    return future;
}

AOS_DEFINE(test_fn_resolve_2, int, int)
aos_future_t *test_fn_resolve_2(aos_future_t *future)
{
    AOS_ARGS_T(test_fn_resolve_2) *args = aos_args_get(future);
    printf("arg1:%d arg2:%d\n", args->arg1, args->arg2);
    aos_resolve(future);
    return future;
}

AOS_DEFINE(test_fn_resolve_3, int, int, int)
aos_future_t *test_fn_resolve_3(aos_future_t *future)
{
    AOS_ARGS_T(test_fn_resolve_3) *args = aos_args_get(future);
    printf("arg1:%d arg2:%d arg3:%d\n", args->arg1, args->arg2, args->arg3);
    aos_resolve(future);
    return future;
}

// AOS_DEFINE(test_fn_reject_0)
// aos_future_t *test_fn_reject_0(aos_future_t *future)
// {
//     printf("no_args\n");
//     _aos_reject(future);
//     return future;
// }

// AOS_DEFINE(test_fn_reject_1, int)
// aos_future_t *test_fn_reject_1(aos_future_t *future)
// {
//     AOS_ARGS_T(test_fn_reject_1) *args = aos_args_get(future);
//     printf("arg1:%d\n", args->arg1);
//     _aos_reject(future);
//     return future;
// }

// AOS_DEFINE(test_fn_reject_2, int, int)
// aos_future_t *test_fn_reject_2(aos_future_t *future)
// {
//     AOS_ARGS_T(test_fn_reject_2) *args = aos_args_get(future);
//     printf("arg1:%d arg2:%d\n", args->arg1, args->arg2);
//     _aos_reject(future);
//     return future;
// }

// AOS_DEFINE(test_fn_reject_3, int, int, int)
// aos_future_t *test_fn_reject_3(aos_future_t *future)
// {
//     AOS_ARGS_T(test_fn_reject_3) *args = aos_args_get(future);
//     printf("arg1:%d arg2:%d arg3:%d\n", args->arg1, args->arg2, args->arg3);
//     _aos_reject(future);
//     return future;
// }
