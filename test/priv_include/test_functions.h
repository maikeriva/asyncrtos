// https://github.com/ThrowTheSwitch/Unity/blob/master/docs/UnityAssertionsReference.md
#include <aos.h>

AOS_DECLARE(test_fn_resolve_0)
aos_future_t *test_fn_resolve_0(aos_future_t *future);

AOS_DECLARE(test_fn_resolve_1, int arg1)
aos_future_t *test_fn_resolve_1(aos_future_t *future);

AOS_DECLARE(test_fn_resolve_2, int arg1, int arg2)
aos_future_t *test_fn_resolve_2(aos_future_t *future);

AOS_DECLARE(test_fn_resolve_3, int arg1, int arg2, int arg3)
aos_future_t *test_fn_resolve_3(aos_future_t *future);
