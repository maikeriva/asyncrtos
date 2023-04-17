/**
 * @file aos_macros.h
 * @author Michele Riva (michele.riva@protonmail.com)
 * @brief AsyncRTOS convenience macros
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
#include <_aos_macros.h>

/**
 * @brief Declare an asynchronous function
 * @param fn_name Function name
 * @param __VA_ARGS__ Function arguments
 */
#define AOS_DECLARE(fn_name, ...) _AOS_DECLARE(fn_name, ##__VA_ARGS__)

/**
 * @brief Define an asynchronous function
 * @param fn_name Function name
 * @param __VA_ARGS__ Function arguments types
 */
#define AOS_DEFINE(fn_name, ...) _AOS_DEFINE(fn_name, ##__VA_ARGS__)

/**
 * @brief Auto-cast to function's arguments struct
 * @param fn_name Function name
 * @return Typed function's arguments struct
 */
#define AOS_ARGS_T(fn_name) _AOS_ARGS_T(fn_name)

/**
 * @brief Auto-cast to function's future allocator
 * @param fn_name Function name
 * @return Function's future allocator
 */
#define AOS_FUTURE_ALLOC_T(fn_name) _AOS_FUTURE_ALLOC_T(fn_name)

/**
 * @brief Auto-cast to function's awaitable allocator
 * @param fn_name Function name
 * @return Function's awaitable future allocator
 */
#define AOS_AWAITABLE_ALLOC_T(fn_name) _AOS_AWAITABLE_ALLOC_T(fn_name)

/**
 * @brief Auto-cast to function's forgettable allocator
 * @param fn_name Function name
 * @return Function's sorgettable future allocator
 */
#define AOS_FORGETTABLE_ALLOC_T(fn_name) _AOS_FORGETTABLE_ALLOC_T(fn_name)

/**
 * @brief Auto-cast to function's eventful allocator
 * @param fn_name Function name
 * @return Function's eventful future allocator
 */
#define AOS_EVENTFUL_ALLOC_T(fn_name) _AOS_EVENTFUL_ALLOC_T(fn_name)
