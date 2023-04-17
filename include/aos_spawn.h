/**
 * @file aos_spawn.h
 * @author Michele Riva (michele.riva@protonmail.com)
 * @brief AsyncRTOS spawn API
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
   * @brief AsyncRTOS spawn
   */
  typedef struct _aos_spawn_t aos_spawn_t;

  /**
   * @brief Spawn configuration
   */
  typedef struct aos_spawn_config_t
  {
    unsigned int stacksize; // Stack size
    unsigned int priority;  // Priority
    const char *name;       // Spawn name
  } aos_spawn_config_t;

  /**
   * @brief Spawn a self-deleting task
   *
   * @param config Configuration
   * @param fn Function to execute in the spawned task
   * @param future Future for the spawned function fn
   * @return Same future as input
   */
  aos_future_t *aos_spawn(aos_spawn_config_t *config, void (*fn)(aos_future_t *), aos_future_t *future);

#ifdef __cplusplus
}
#endif
