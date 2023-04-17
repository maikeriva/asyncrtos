/**
 * @file _aos_future.h
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
#pragma once
#include <aos_future.h>

#ifdef __cplusplus
extern "C"
{
#endif

  typedef enum
  {
    AOS_STATE_NEW,
    AOS_STATE_RESOLVED,
    AOS_STATE_REJECTED,
  } _aos_state_t;

  struct _aos_future_t
  {
    _aos_state_t state;
    void (*cb)(struct _aos_future_t *);
    void *ctx;
    void *args;
  };

  void _aos_reject(aos_future_t *future);

#ifdef __cplusplus
}
#endif
