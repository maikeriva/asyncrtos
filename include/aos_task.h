/**
 * @file aos_task.h
 * @author Michele Riva (michele.riva@protonmail.com)
 * @brief AsyncRTOS task API
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
#pragma once
#include <aos_future.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief AsyncRTOS task
     */
    typedef struct _aos_task_t aos_task_t;

    /**
     * @brief Task handler prototype
     */
    typedef void (*aos_task_handler_t)(aos_task_t *task, aos_future_t *future);

    /**
     * @brief Set a task handler for a task
     *
     * @warning This is safe to call only before a task is started or within the task itself
     *
     * @param task Task
     * @param handler Handler
     * @param event Event which will trigger the handler (typically an enum)
     * @return unsigned int 0 if success, other if fail
     */
    unsigned int aos_task_handler_set(aos_task_t *task, aos_task_handler_t handler, int event);

    /**
     * @brief Unset a task handler for a task
     *
     * @warning This is safe to call only before a task is started or within the task itself
     *
     * @param task Task
     * @param event Event which triggers the handler
     */
    void aos_task_handler_unset(aos_task_t *task, int event);

    /**
     * @brief Check if task is stopping.
     *
     * This is useful in IPC response handlers, as they handle enqueued responses even when the task is stopping.
     * This is to prevent losing any context which may have been assigned to the IPC future.
     *
     * @param task Task
     * @return true if stopping, false otherwise
     */
    bool aos_task_isstopping(aos_task_t *task);

    /**
     * @brief Task loop prototype
     */
    typedef void (*aos_task_loop_t)(aos_task_t *task);

    /**
     * @brief Task loop handle
     */
    typedef struct _aos_task_loop_entry_t aos_task_loop_handle_t;

    /**
     * @brief Set a task loop for a task
     *
     * @warning This is safe to call only before a task is started or within the task itself
     *
     * @param task Task
     * @param loop Loop
     * @param interval_ms Interval in ms between iterations
     * @return Loop handle if success, NULL otherwise
     */
    aos_task_loop_handle_t *aos_task_loop_set(aos_task_t *task, aos_task_loop_t loop, unsigned int interval_ms);

    /**
     * @brief Unset a task loop for a task
     *
     * @warning This is safe to call only before a task is started or within the task itself
     *
     * @param task Task
     * @param handle Loop handle
     */
    void aos_task_loop_unset(aos_task_t *task, aos_task_loop_handle_t *handle);

    /**
     * @brief Task hook prototype.
     *
     * Task hooks must return 0 if executed successfully.
     * Any other return value will imply a failure and cause the task to abort the respective operation (start or stop).
     */
    typedef unsigned int (*aos_task_hook_t)(aos_task_t *task, aos_future_t *future);

    /**
     * @brief Task configuration struct
     */
    typedef struct aos_task_config
    {
        unsigned int stacksize;  // Stack size
        unsigned int queuesize;  // Queue size
        unsigned int priority;   // Priority
        aos_task_hook_t onstart; // Hook to call on task start
        aos_task_hook_t onstop;  // Hook to call on task stop
        const char *name;        // Task name
        void *args;              // Task arguments
    } aos_task_config_t;

    /**
     * @brief Allocate a new task
     *
     * @param config Configuration
     * @return Task if success, NULL otherwise
     */
    aos_task_t *aos_task_alloc(aos_task_config_t *config);

    /**
     * @brief Free a task
     *
     * @warning Tasks need to be stopped prior being freed
     *
     * @param task Task
     */
    void aos_task_free(aos_task_t *task);

    /**
     * @brief Start a task.
     *
     * Starting a task will call the onstart task hook if any is configured.
     *
     * @param task Task
     * @param future Future for the start hook (if any). If no start hook is set, a generic future.
     * @return Same future as input
     */
    aos_future_t *aos_task_start(aos_task_t *task, aos_future_t *future);

    /**
     * @brief Stop a task.
     *
     * Stopping a task will call the onstop task hook if any is configured.
     *
     * @param task Task
     * @param future Future for the stop hook (if any). If no stop hook is set, a generic future.
     * @return Same future as input
     */
    aos_future_t *aos_task_stop(aos_task_t *task, aos_future_t *future);

    /**
     * @brief Send a message to a task
     *
     * @param task Task
     * @param event Event to invoke
     * @param future Future for the invoked event
     * @return Same future as input
     */
    aos_future_t *aos_task_send(aos_task_t *task, int event, aos_future_t *future);

    /**
     * @brief Get task arguments
     *
     * @param task Task
     * @return Task arguments if any
     */
    void *aos_task_args_get(aos_task_t *task);

#ifdef __cplusplus
}
#endif
