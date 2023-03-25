/**
 * Copyright 2021-2023 Michele Riva
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
#pragma once
#include <aos_future.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct _aos_task_t aos_task_t;

    typedef void (*aos_task_handler_t)(aos_task_t *task, aos_future_t *future);
    unsigned int aos_task_handler_set(aos_task_t *task, aos_task_handler_t handler, AOS_ENUM_T event);
    void aos_task_handler_unset(aos_task_t *task, AOS_ENUM_T event);
    bool aos_task_isstopping(aos_task_t *task);

    typedef unsigned int (*aos_task_loop_t)(aos_task_t *task);
    typedef struct _aos_task_loop_entry_t aos_task_loop_entry_t;
    aos_task_loop_entry_t* aos_task_loop_set(aos_task_t *task, aos_task_loop_t loop, unsigned int interval_ms);
    void aos_task_loop_unset(aos_task_t *task, aos_task_loop_entry_t* handle);

    typedef unsigned int (*aos_task_hook_t)(aos_task_t *task, aos_future_t *future);

    typedef struct aos_task_config
    {
        unsigned int stacksize;
        unsigned int queuesize;
        unsigned int priority;
        aos_task_hook_t *onstart;
        aos_task_hook_t *onstop;
        // bool rejectonshutdown;
        const char *name;
        void *args;
    } aos_task_config_t;

    aos_task_t *aos_task_alloc(aos_task_config_t *config);
    void aos_task_free(aos_task_t *task);

    aos_future_t *aos_task_start(aos_task_t *task, aos_future_t *future);
    aos_future_t *aos_task_stop(aos_task_t *task, aos_future_t *future);
    aos_future_t *aos_task_send(aos_task_t *task, AOS_ENUM_T event, aos_future_t *future);

    void *aos_task_args_get(aos_task_t *task);

#ifdef __cplusplus
}
#endif
