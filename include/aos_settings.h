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
 */
#pragma once
#include <stdint.h>

/**
 * @brief ESP_IDF platform configuration
 */
#define AOS_ENUM_T int32_t
#define AOS_ENUM_MIN INT32_MIN
// #define AOS_DECLARED_T uint8_t // FIXME: Maybe now unnecessary
#define AOS_TASK_NAMEMAXLEN 12
#define AOS_TASK_STACKSIZEDEFAULT 2048
#define AOS_TASK_QUEUESIZEDEFAULT 3
#define AOS_TASK_PRIORITYDEFAULT 2
