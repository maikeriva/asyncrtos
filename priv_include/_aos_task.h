#include <aos_task.h>

typedef struct _aos_task_msg_t
{
    AOS_ENUM_T event;
    aos_future_t *future;
} _aos_task_msg_t;
