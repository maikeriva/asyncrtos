/**
 * @file aos_future_awaitable.h
 * @author Michele Riva (michele.riva@protonmail.com)
 * @brief AsyncRTOS awaitable future API
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
   * @brief Allocate awaitable future
   *
   * @param args_size Size of attached arguments
   * @return Future if success, NULL otherwise
   */
  aos_future_t *aos_awaitable_alloc(size_t args_size);

  /**
   * @brief Await an awaitable future
   *
   * @param future Awaitable future
   * @return Same future as input
   */
  aos_future_t *aos_await(aos_future_t *future);

  /**
   * @brief Free awaitable future
   *
   * @param future Future
   */
  void aos_awaitable_free(aos_future_t *future);

#ifdef __cplusplus
}
#endif
