// https://github.com/ThrowTheSwitch/Unity/blob/master/docs/UnityAssertionsReference.md
#include <aos.h>

enum {
    PRINT0,
    PRINT1,
    FORWARD,
    FORWARD_ITC,
};

AOS_DECLARE(task1_print0)
void task1_print0_handler(aos_task_t *task, aos_future_t *future);

AOS_DECLARE(task1_print1,int arg1)
void task1_print1_handler(aos_task_t *task, aos_future_t *future);

AOS_DECLARE(task1_start)
unsigned int task1_start_hook(aos_task_t *task, aos_future_t *future);

AOS_DECLARE(task1_stop)
unsigned int task1_stop_hook(aos_task_t *task, aos_future_t *future);

void task1_loop0(aos_task_t *task);

void task1_loop1(aos_task_t *task);
