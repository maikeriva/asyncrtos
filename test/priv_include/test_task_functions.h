// https://github.com/ThrowTheSwitch/Unity/blob/master/docs/UnityAssertionsReference.md
#include <aos.h>

enum {
    PRINT0,
    PRINT1,
    FORWARD,
    FORWARDCB,
};

AOS_DECLARE(task_print0)
void task_print0_handler(aos_task_t *task, aos_future_t *future);

AOS_DECLARE(task_print1,int arg1)
void task_print1_handler(aos_task_t *task, aos_future_t *future);

AOS_DECLARE(task_forward,aos_task_t* task)
void task_forward_handler(aos_task_t *task, aos_future_t *future);
void task_forward_cb_handler(aos_task_t *task, aos_future_t *future);

AOS_DECLARE(task_start)
unsigned int task_start_hook(aos_task_t *task, aos_future_t *future);

AOS_DECLARE(task_stop)
unsigned int task_stop_hook(aos_task_t *task, aos_future_t *future);

void task_loop0(aos_task_t *task);

void task_loop1(aos_task_t *task);
