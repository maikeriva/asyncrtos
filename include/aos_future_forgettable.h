/**
 * @file aos_future_forgettable.h
 * @author Michele Riva (michele.riva@protonmail.com)
 * @brief AsyncRTOS forgettable future API
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
   * @brief Allocate a forgettable future.
   *
   * Forgettable futures auto-free themselves and their attached context once
   * resolved without calling back anything.
   * They are useful to send notifications to tasks.
   *
   * @param args_size Size of attached arguments
   * @return Future if success, NULL otherwise
   */
  aos_future_t *aos_forgettable_alloc(size_t args_size);

#ifdef __cplusplus
}
#endif
