/**
 * @file aos_future_eventful.h
 * @author Michele Riva (michele.riva@protonmail.com)
 * @brief AsyncRTOS eventful future API
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
#include <aos_task.h>

#ifdef __cplusplus
extern "C"
{
#endif

  /**
   * @brief Eventful future configuration
   */
  typedef struct aos_eventful_config_t
  {
    aos_task_t *task; // Task to respond to
    int event;        // Event to raise on response
    void *ctx;        // Context (optional)
  } aos_eventful_config_t;

  /**
   * @brief Allocate eventful future
   *
   * @param config Configuration
   * @param args_size Size of attached arguments
   * @return Future if success, NULL otherwise
   */
  aos_future_t *aos_eventful_alloc(aos_eventful_config_t *config, size_t args_size);

  /**
   * @brief Free eventful future
   *
   * @param future Future
   * @return Context attached to future (if any)
   */
  void *aos_eventful_free(aos_future_t *future);

#ifdef __cplusplus
}
#endif
