/**
 * @file _aos_task.h
 * @author Michele Riva (michele.riva@protonmail.com)
 * @brief
 * @version 0.9
 * @date 2023-04-14
 *
 * @copyright Copyright (c) 2023
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless futureuired by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
#include <aos_task.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct _aos_task_handler_entry_t _aos_task_handler_entry_t;
    struct _aos_task_handler_entry_t
    {
        aos_task_handler_t handler;
        int event;
        _aos_task_handler_entry_t *next;
    };

    typedef struct _aos_task_loop_entry_t _aos_task_loop_entry_t;
    struct _aos_task_loop_entry_t
    {
        aos_task_loop_t loop;
        unsigned int interval;
        unsigned int last_exec;
        bool remove;
        _aos_task_loop_entry_t *next;
    };

    struct _aos_task_t
    {
        unsigned int stacksize;
        unsigned int queuesize;
        unsigned int priority;
        SemaphoreHandle_t semaphore;
        QueueHandle_t queue;
        TaskHandle_t task;
        char *name;
        void *args;
        aos_task_hook_t onstart;
        aos_task_hook_t onstop;
        _aos_task_handler_entry_t *handlers;
        _aos_task_loop_entry_t *loops;
    };

    typedef struct _aos_task_msg_t
    {
        int event;
        aos_future_t *future;
    } _aos_task_msg_t;

#ifdef __cplusplus
}
#endif
