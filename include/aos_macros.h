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
#include <_aos_macros.h>

/**
 * @brief Declare aos function
 * @param fn_name Function name
 * @param __VA_ARGS__ Arguments
 */
#define AOS_DECLARE(fn_name, ...) _AOS_DECLARE(fn_name, ## __VA_ARGS__)

/**
 * @brief Define aos function
 * @param fn_name Function name
 * @param __VA_ARGS__ Arguments
 */
#define AOS_DEFINE(fn_name, ...) _AOS_DEFINE(fn_name, ##__VA_ARGS__)

/**
 * @brief Translates to fn_name args type
 * @param fn_name Function name
 * @return Type of function arguments struct
 */
#define AOS_ARGS_T(fn_name) _AOS_ARGS_T(fn_name)

/**
 * @brief Get future allocator for function fn_name
 * @param fn_name Function name
 * @return Generic future allocator
 */
#define AOS_FUTURE_ALLOC_T(fn_name) _AOS_FUTURE_ALLOC_T(fn_name)

/**
 * @brief Get awaitable future allocator for function fn_name
 * @param fn_name Function name
 * @return Awaitable future allocator
 */
#define AOS_AWAITABLE_ALLOC_T(fn_name) _AOS_AWAITABLE_ALLOC_T(fn_name)

/**
 * @brief Get forgettable future allocator for function fn_name
 * @param fn_name Function name
 * @return Forgettable future allocator
 */
#define AOS_FORGETTABLE_ALLOC_T(fn_name) _AOS_FORGETTABLE_ALLOC_T(fn_name)

/**
 * @brief Get eventful future allocator for function fn_name
 * @param fn_name Function name
 * @return Eventful future allocator
 */
#define AOS_EVENTFUL_ALLOC_T(fn_name) _AOS_EVENTFUL_ALLOC_T(fn_name)
