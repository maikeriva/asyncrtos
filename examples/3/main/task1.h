#pragma once
#include <aos.h>

#ifdef __cplusplus
extern "C"
{
#endif

    AOS_DECLARE(task1_sayhello)
    aos_future_t *task1_sayhello(aos_future_t *future);

    void task1_init();

#ifdef __cplusplus
}
#endif
