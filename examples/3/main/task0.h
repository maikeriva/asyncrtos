#pragma once
#include <aos.h>

#ifdef __cplusplus
extern "C"
{
#endif

    AOS_DECLARE(task0_dosomething)
    aos_future_t *task0_dosomething(aos_future_t *future);

    void task0_init();

#ifdef __cplusplus
}
#endif
