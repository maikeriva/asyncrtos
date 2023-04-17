/**
 * @file aos_future.h
 * @author Michele Riva (michele.riva@protonmail.com)
 * @brief AsyncRTOS generic future API
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
#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

  /**
   * @brief Future
   */
  typedef struct _aos_future_t aos_future_t;

  /**
   * @brief Get future's arguments
   *
   * @param future Future
   * @return void* Pointer to future's arguments
   */
  void *aos_args_get(aos_future_t *future);

  /**
   * @brief Resolve a future
   *
   * @param future Future
   */
  void aos_resolve(aos_future_t *future);

  /**
   * @brief Check if a future has been resolved
   *
   * @param future Future
   * @return true if resolved, false otherwise
   */
  bool aos_isresolved(aos_future_t *future);

  /**
   * @brief Generic future configuration
   */
  typedef struct aos_future_config_t
  {
    void (*cb)(aos_future_t *); // Callback
    void *ctx;                  // Context (optional)
  } aos_future_config_t;

  /**
   * @brief Allocate a generic future
   *
   * @param config Configuration
   * @param args_size Size of attached arguments
   * @return Future if success, NULL otherwise
   */
  aos_future_t *aos_future_alloc(aos_future_config_t *config, size_t args_size);

  /**
   * @brief Free a generic future
   *
   * @param future Future
   * @return Context attached to future (if any)
   */
  void *aos_future_free(aos_future_t *future);

#ifdef __cplusplus
}
#endif
