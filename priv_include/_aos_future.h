/**
 * Copyright 2021-2023 Michele Riva
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
 *
 * TODO:
 * - Consider whether to introduce an aos_deallocator_t parameter to futures, which will be called when it is necessary to deallocate a more complex parameter structure.
 * - Consider introducing .handlers and .handlers_count fields to aos_task_config_t, so that handlers can be set through a declarative approach.
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
  } _aos_state_t;

  struct _aos_future_t
  {
    _aos_state_t state;
    aos_cb_t cb;
    void *ctx;
    void *args;
  };

#ifdef __cplusplus
}
#endif
