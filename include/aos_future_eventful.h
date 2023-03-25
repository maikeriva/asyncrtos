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
#include <aos_task.h>

#ifdef __cplusplus
extern "C"
{
#endif

  typedef struct aos_eventful_config_t
  {
    aos_task_t *task;
    AOS_ENUM_T event;
    void *ctx;
  } aos_eventful_config_t;
  aos_future_t *aos_eventful_alloc(aos_eventful_config_t *config, size_t args_size);
  void *aos_eventful_free(aos_future_t *future);

#ifdef __cplusplus
}
#endif
