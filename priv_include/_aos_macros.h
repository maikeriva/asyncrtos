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
 * - Complete conditional compiling depending on AOS_TASK
 *
 * FIXME: Check _AOS_DECLARE_0 works this way, or else we have to fall back to:
 * typedef void fn_name##_##tag##_args_t;
 * typedef void fn_name##_##tag##_args_declared;
 *     typedef AOS_DECLARED_T##fn_name##_args_declared;
 * - IMPORTANT: Should we possibly keep the possibility of alloc(void*), thus NOT duplicating parameters, for advanced users?
 *   It would require us to cleanup ALLOC_T()() with corresponding FREE_T()() calls... Which could be overridden if anyone wants to.
 */
#pragma once
#include <_aos_future.h>
#include <_aos_task.h>
#include <aos_future_awaitable.h>
#include <aos_future_forgettable.h>
#include <aos_future_eventful.h>
#include <stddef.h>

#define _AOS_ARGS_T(fn_name) fn_name##_args_t
#define _AOS_FUTURE_ALLOC_T(fn_name) fn_name##_future_alloc
#define _AOS_AWAITABLE_ALLOC_T(fn_name) fn_name##_awaitable_alloc
#define _AOS_FORGETTABLE_ALLOC_T(fn_name) fn_name##_forgettable_alloc
#define _AOS_EVENTFUL_ALLOC_T(fn_name) fn_name##_eventful_alloc

#define _AOS_MACRO_SELECTOR(a, b, c, d, e, f, g, h, i, N, ...) N

#define _AOS_DECLARE_0(fn_name)                                          \
    typedef struct fn_name##_args_t                                        \
    {                                                                      \
    } fn_name##_args_t;                                                    \
    aos_future_t *fn_name##_future_alloc(aos_future_config_t *config); \
    aos_future_t *fn_name##_awaitable_alloc();                           \
    aos_future_t *fn_name##_forgettable_alloc();                         \
    aos_future_t *fn_name##_eventful_alloc(aos_eventful_config_t *config);
#define _AOS_DECLARE_1(fn_name, p1)                                          \
    typedef struct fn_name##_args_t                                            \
    {                                                                          \
        p1;                                                                    \
    } fn_name##_args_t;                                                        \
    aos_future_t *fn_name##_future_alloc(aos_future_config_t *config, p1); \
    aos_future_t *fn_name##_awaitable_alloc(p1);                             \
    aos_future_t *fn_name##_forgettable_alloc(p1);                           \
    aos_future_t *fn_name##_eventful_alloc(aos_eventful_config_t *config, p1);
#define _AOS_DECLARE_2(fn_name, p1, p2)                                          \
    typedef struct fn_name##_args_t                                                \
    {                                                                              \
        p1;                                                                        \
        p2;                                                                        \
    } fn_name##_args_t;                                                            \
    aos_future_t *fn_name##_future_alloc(aos_future_config_t *config, p1, p2); \
    aos_future_t *fn_name##_awaitable_alloc(p1, p2);                             \
    aos_future_t *fn_name##_forgettable_alloc(p1, p2);                           \
    aos_future_t *fn_name##_eventful_alloc(aos_eventful_config_t *config, p1, p2);
#define _AOS_DECLARE_3(fn_name, p1, p2, p3)                                          \
    typedef struct fn_name##_args_t                                                    \
    {                                                                                  \
        p1;                                                                            \
        p2;                                                                            \
        p3;                                                                            \
    } fn_name##_args_t;                                                                \
    aos_future_t *fn_name##_future_alloc(aos_future_config_t *config, p1, p2, p3); \
    aos_future_t *fn_name##_awaitable_alloc(p1, p2, p3);                             \
    aos_future_t *fn_name##_forgettable_alloc(p1, p2, p3);                           \
    aos_future_t *fn_name##_eventful_alloc(aos_eventful_config_t *config, p1, p2, p3);
#define _AOS_DECLARE_4(fn_name, p1, p2, p3, p4)                                          \
    typedef struct fn_name##_args_t                                                        \
    {                                                                                      \
        p1;                                                                                \
        p2;                                                                                \
        p3;                                                                                \
        p4;                                                                                \
    } fn_name##_args_t;                                                                    \
    aos_future_t *fn_name##_future_alloc(aos_future_config_t *config, p1, p2, p3, p4); \
    aos_future_t *fn_name##_awaitable_alloc(p1, p2, p3, p4);                             \
    aos_future_t *fn_name##_forgettable_alloc(p1, p2, p3, p4);                           \
    aos_future_t *fn_name##_eventful_alloc(aos_eventful_config_t *config, p1, p2, p3, p4);
#define _AOS_DECLARE_5(fn_name, p1, p2, p3, p4, p5)                                          \
    typedef struct fn_name##_args_t                                                            \
    {                                                                                          \
        p1;                                                                                    \
        p2;                                                                                    \
        p3;                                                                                    \
        p4;                                                                                    \
        p5;                                                                                    \
    } fn_name##_args_t;                                                                        \
    aos_future_t *fn_name##_future_alloc(aos_future_config_t *config, p1, p2, p3, p4, p5); \
    aos_future_t *fn_name##_awaitable_alloc(p1, p2, p3, p4, p5);                             \
    aos_future_t *fn_name##_forgettable_alloc(p1, p2, p3, p4, p5);                           \
    aos_future_t *fn_name##_eventful_alloc(aos_eventful_config_t *config, p1, p2, p3, p4, p5);
#define _AOS_DECLARE_6(fn_name, p1, p2, p3, p4, p5, p6)                                          \
    typedef struct fn_name##_args_t                                                                \
    {                                                                                              \
        p1;                                                                                        \
        p2;                                                                                        \
        p3;                                                                                        \
        p4;                                                                                        \
        p5;                                                                                        \
        p6;                                                                                        \
    } fn_name##_args_t;                                                                            \
    aos_future_t *fn_name##_future_alloc(aos_future_config_t *config, p1, p2, p3, p4, p5, p6); \
    aos_future_t *fn_name##_awaitable_alloc(p1, p2, p3, p4, p5, p6);                             \
    aos_future_t *fn_name##_forgettable_alloc(p1, p2, p3, p4, p5, p6);                           \
    aos_future_t *fn_name##_eventful_alloc(aos_eventful_config_t *config, p1, p2, p3, p4, p5, p6);
#define _AOS_DECLARE_7(fn_name, p1, p2, p3, p4, p5, p6, p7)                                          \
    typedef struct fn_name##_args_t                                                                    \
    {                                                                                                  \
        p1;                                                                                            \
        p2;                                                                                            \
        p3;                                                                                            \
        p4;                                                                                            \
        p5;                                                                                            \
        p6;                                                                                            \
        p7;                                                                                            \
    } fn_name##_args_t;                                                                                \
    aos_future_t *fn_name##_future_alloc(aos_future_config_t *config, p1, p2, p3, p4, p5, p6, p7); \
    aos_future_t *fn_name##_awaitable_alloc(p1, p2, p3, p4, p5, p6, p7);                             \
    aos_future_t *fn_name##_forgettable_alloc(p1, p2, p3, p4, p5, p6, p7);                           \
    aos_future_t *fn_name##_eventful_alloc(aos_eventful_config_t *config, p1, p2, p3, p4, p5, p6, p7);
#define _AOS_DECLARE_8(fn_name, p1, p2, p3, p4, p5, p6, p7, p8)                                          \
    typedef struct fn_name##_args_t                                                                        \
    {                                                                                                      \
        p1;                                                                                                \
        p2;                                                                                                \
        p3;                                                                                                \
        p4;                                                                                                \
        p5;                                                                                                \
        p6;                                                                                                \
        p7;                                                                                                \
        p8;                                                                                                \
    } fn_name##_args_t;                                                                                    \
    aos_future_t *fn_name##_future_alloc(aos_future_config_t *config, p1, p2, p3, p4, p5, p6, p7, p8); \
    aos_future_t *fn_name##_awaitable_alloc(p1, p2, p3, p4, p5, p6, p7, p8);                             \
    aos_future_t *fn_name##_forgettable_alloc(p1, p2, p3, p4, p5, p6, p7, p8);                           \
    aos_future_t *fn_name##_eventful_alloc(aos_eventful_config_t *config, p1, p2, p3, p4, p5, p6, p7, p8);

#define _AOS_DECLARE(fn_name, ...)           \
    _AOS_MACRO_SELECTOR(NULL, ##__VA_ARGS__, \
                          _AOS_DECLARE_8,    \
                          _AOS_DECLARE_7,    \
                          _AOS_DECLARE_6,    \
                          _AOS_DECLARE_5,    \
                          _AOS_DECLARE_4,    \
                          _AOS_DECLARE_3,    \
                          _AOS_DECLARE_2,    \
                          _AOS_DECLARE_1,    \
                          _AOS_DECLARE_0)    \
    (fn_name, ##__VA_ARGS__)

#define _AOS_DEFINE_0(fn_name)                                              \
    aos_future_t *fn_name##_future_alloc(aos_future_config_t *config)     \
    {                                                                         \
        return aos_future_alloc(config, 0);                                 \
    }                                                                         \
    aos_future_t *fn_name##_awaitable_alloc()                               \
    {                                                                         \
        return aos_awaitable_alloc(0);                                      \
    }                                                                         \
    aos_future_t *fn_name##_forgettable_alloc()                             \
    {                                                                         \
        return aos_forgettable_alloc(0);                                    \
    }                                                                         \
    aos_future_t *fn_name##_eventful_alloc(aos_eventful_config_t *config) \
    {                                                                         \
        return aos_eventful_alloc(config, 0);                               \
    }
#define _AOS_DEFINE_1(fn_name, t1)                                                 \
    aos_future_t *fn_name##_future_alloc(aos_future_config_t *config, t1 p1)     \
    {                                                                                \
        aos_future_t *future = aos_future_alloc(config, sizeof(t1));             \
        if (!future)                                                                 \
            return NULL;                                                             \
        memcpy(future->args, &p1, sizeof(t1));                                       \
        return future;                                                               \
    }                                                                                \
    aos_future_t *fn_name##_awaitable_alloc(t1 p1)                                 \
    {                                                                                \
        aos_future_t *future = aos_awaitable_alloc(sizeof(t1));                  \
        if (!future)                                                                 \
            return NULL;                                                             \
        memcpy(future->args, &p1, sizeof(t1));                                       \
        return future;                                                               \
    }                                                                                \
    aos_future_t *fn_name##_forgettable_alloc(t1 p1)                               \
    {                                                                                \
        aos_future_t *future = aos_forgettable_alloc(sizeof(t1));                \
        if (!future)                                                                 \
            return NULL;                                                             \
        memcpy(future->args, &p1, sizeof(t1));                                       \
        return future;                                                               \
    }                                                                                \
    aos_future_t *fn_name##_eventful_alloc(aos_eventful_config_t *config, t1 p1) \
    {                                                                                \
        aos_future_t *future = aos_eventful_alloc(config, sizeof(t1));           \
        if (!future)                                                                 \
            return NULL;                                                             \
        memcpy(future->args, &p1, sizeof(t1));                                       \
        return future;                                                               \
    }
#define _AOS_DEFINE_2(fn_name, t1, t2)                                                    \
    aos_future_t *fn_name##_future_alloc(aos_future_config_t *config, t1 p1, t2 p2)     \
    {                                                                                       \
        aos_future_t *future = aos_future_alloc(config, sizeof(t1) + sizeof(t2));       \
        if (!future)                                                                        \
            return NULL;                                                                    \
        memcpy(future->args, &p1, sizeof(t1));                                              \
        memcpy(future->args + sizeof(t1), &p2, sizeof(t2));                                 \
        return future;                                                                      \
    }                                                                                       \
    aos_future_t *fn_name##_awaitable_alloc(t1 p1, t2 p2)                                 \
    {                                                                                       \
        aos_future_t *future = aos_awaitable_alloc(sizeof(t1) + sizeof(t2));            \
        if (!future)                                                                        \
            return NULL;                                                                    \
        memcpy(future->args, &p1, sizeof(t1));                                              \
        memcpy(future->args + sizeof(t1), &p2, sizeof(t2));                                 \
        return future;                                                                      \
    }                                                                                       \
    aos_future_t *fn_name##_forgettable_alloc(t1 p1, t2 p2)                               \
    {                                                                                       \
        aos_future_t *future = aos_forgettable_alloc(sizeof(t1) + sizeof(t2));          \
        if (!future)                                                                        \
            return NULL;                                                                    \
        memcpy(future->args, &p1, sizeof(t1));                                              \
        memcpy(future->args + sizeof(t1), &p2, sizeof(t2));                                 \
        return future;                                                                      \
    }                                                                                       \
    aos_future_t *fn_name##_eventful_alloc(aos_eventful_config_t *config, t1 p1, t2 p2) \
    {                                                                                       \
        aos_future_t *future = aos_eventful_alloc(config, sizeof(t1) + sizeof(t2));     \
        if (!future)                                                                        \
            return NULL;                                                                    \
        memcpy(future->args, &p1, sizeof(t1));                                              \
        memcpy(future->args + sizeof(t1), &p2, sizeof(t2));                                 \
        return future;                                                                      \
    }
#define _AOS_DEFINE_3(fn_name, t1, t2, t3)                                                         \
    aos_future_t *fn_name##_future_alloc(aos_future_config_t *config, t1 p1, t2 p2, t3 p3)       \
    {                                                                                                \
        aos_future_t *future = aos_future_alloc(config, sizeof(t1) + sizeof(t2) + sizeof(t3));   \
        if (!future)                                                                                 \
            return NULL;                                                                             \
        memcpy(future->args, &p1, sizeof(t1));                                                       \
        memcpy(future->args + sizeof(t1), &p2, sizeof(t2));                                          \
        memcpy(future->args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                             \
        return future;                                                                               \
    }                                                                                                \
    aos_future_t *fn_name##_awaitable_alloc(t1 p1, t2 p2, t3 p3)                                   \
    {                                                                                                \
        aos_future_t *future = aos_awaitable_alloc(sizeof(t1) + sizeof(t2) + sizeof(t3));        \
        if (!future)                                                                                 \
            return NULL;                                                                             \
        memcpy(future->args, &p1, sizeof(t1));                                                       \
        memcpy(future->args + sizeof(t1), &p2, sizeof(t2));                                          \
        memcpy(future->args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                             \
        return future;                                                                               \
    }                                                                                                \
    aos_future_t *fn_name##_forgettable_alloc(t1 p1, t2 p2, t3 p3)                                 \
    {                                                                                                \
        aos_future_t *future = aos_forgettable_alloc(sizeof(t1) + sizeof(t2) + sizeof(t3));      \
        if (!future)                                                                                 \
            return NULL;                                                                             \
        memcpy(future->args, &p1, sizeof(t1));                                                       \
        memcpy(future->args + sizeof(t1), &p2, sizeof(t2));                                          \
        memcpy(future->args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                             \
        return future;                                                                               \
    }                                                                                                \
    aos_future_t *fn_name##_eventful_alloc(aos_eventful_config_t *config, t1 p1, t2 p2, t3 p3)   \
    {                                                                                                \
        aos_future_t *future = aos_eventful_alloc(config, sizeof(t1) + sizeof(t2) + sizeof(t3)); \
        if (!future)                                                                                 \
            return NULL;                                                                             \
        memcpy(future->args, &p1, sizeof(t1));                                                       \
        memcpy(future->args + sizeof(t1), &p2, sizeof(t2));                                          \
        memcpy(future->args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                             \
        return future;                                                                               \
    }
#define _AOS_DEFINE_4(fn_name, t1, t2, t3, t4)                                                                  \
    aos_future_t *fn_name##_future_alloc(aos_future_config_t *config, t1 p1, t2 p2, t3 p3, t4 p4)             \
    {                                                                                                             \
        aos_future_t *future = aos_future_alloc(config, sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4));   \
        if (!future)                                                                                              \
            return NULL;                                                                                          \
        memcpy(future->args, &p1, sizeof(t1));                                                                    \
        memcpy(future->args + sizeof(t1), &p2, sizeof(t2));                                                       \
        memcpy(future->args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                          \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                             \
        return future;                                                                                            \
    }                                                                                                             \
    aos_future_t *fn_name##_awaitable_alloc(t1 p1, t2 p2, t3 p3, t4 p4)                                         \
    {                                                                                                             \
        aos_future_t *future = aos_awaitable_alloc(sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4));        \
        if (!future)                                                                                              \
            return NULL;                                                                                          \
        memcpy(future->args, &p1, sizeof(t1));                                                                    \
        memcpy(future->args + sizeof(t1), &p2, sizeof(t2));                                                       \
        memcpy(future->args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                          \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                             \
        return future;                                                                                            \
    }                                                                                                             \
    aos_future_t *fn_name##_forgettable_alloc(t1 p1, t2 p2, t3 p3, t4 p4)                                       \
    {                                                                                                             \
        aos_future_t *future = aos_forgettable_alloc(sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4));      \
        if (!future)                                                                                              \
            return NULL;                                                                                          \
        memcpy(future->args, &p1, sizeof(t1));                                                                    \
        memcpy(future->args + sizeof(t1), &p2, sizeof(t2));                                                       \
        memcpy(future->args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                          \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                             \
        return future;                                                                                            \
    }                                                                                                             \
    aos_future_t *fn_name##_eventful_alloc(aos_eventful_config_t *config, t1 p1, t2 p2, t3 p3, t4 p4)         \
    {                                                                                                             \
        aos_future_t *future = aos_eventful_alloc(config, sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4)); \
        if (!future)                                                                                              \
            return NULL;                                                                                          \
        memcpy(future->args, &p1, sizeof(t1));                                                                    \
        memcpy(future->args + sizeof(t1), &p2, sizeof(t2));                                                       \
        memcpy(future->args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                          \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                             \
        return future;                                                                                            \
    }
#define _AOS_DEFINE_5(fn_name, t1, t2, t3, t4, t5)                                                                           \
    aos_future_t *fn_name##_future_alloc(aos_future_config_t *config, t1 p1, t2 p2, t3 p3, t4 p4, t5 p5)                   \
    {                                                                                                                          \
        aos_future_t *future = aos_future_alloc(config, sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5));   \
        if (!future)                                                                                                           \
            return NULL;                                                                                                       \
        memcpy(future->args, &p1, sizeof(t1));                                                                                 \
        memcpy(future->args + sizeof(t1), &p2, sizeof(t2));                                                                    \
        memcpy(future->args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                                       \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                                          \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4), &p5, sizeof(t5));                             \
        return future;                                                                                                         \
    }                                                                                                                          \
    aos_future_t *fn_name##_awaitable_alloc(t1 p1, t2 p2, t3 p3, t4 p4, t5 p5)                                               \
    {                                                                                                                          \
        aos_future_t *future = aos_awaitable_alloc(sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5));        \
        if (!future)                                                                                                           \
            return NULL;                                                                                                       \
        memcpy(future->args, &p1, sizeof(t1));                                                                                 \
        memcpy(future->args + sizeof(t1), &p2, sizeof(t2));                                                                    \
        memcpy(future->args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                                       \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                                          \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4), &p5, sizeof(t5));                             \
        return future;                                                                                                         \
    }                                                                                                                          \
    aos_future_t *fn_name##_forgettable_alloc(t1 p1, t2 p2, t3 p3, t4 p4, t5 p5)                                             \
    {                                                                                                                          \
        aos_future_t *future = aos_forgettable_alloc(sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5));      \
        if (!future)                                                                                                           \
            return NULL;                                                                                                       \
        memcpy(future->args, &p1, sizeof(t1));                                                                                 \
        memcpy(future->args + sizeof(t1), &p2, sizeof(t2));                                                                    \
        memcpy(future->args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                                       \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                                          \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4), &p5, sizeof(t5));                             \
        return future;                                                                                                         \
    }                                                                                                                          \
    aos_future_t *fn_name##_eventful_alloc(aos_eventful_config_t *config, t1 p1, t2 p2, t3 p3, t4 p4, t5 p5)               \
    {                                                                                                                          \
        aos_future_t *future = aos_eventful_alloc(config, sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5)); \
        if (!future)                                                                                                           \
            return NULL;                                                                                                       \
        memcpy(future->args, &p1, sizeof(t1));                                                                                 \
        memcpy(future->args + sizeof(t1), &p2, sizeof(t2));                                                                    \
        memcpy(future->args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                                       \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                                          \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4), &p5, sizeof(t5));                             \
        return future;                                                                                                         \
    }
#define _AOS_DEFINE_6(fn_name, t1, t2, t3, t4, t5, t6)                                                                                    \
    aos_future_t *fn_name##_future_alloc(aos_future_config_t *config, t1 p1, t2 p2, t3 p3, t4 p4, t5 p5, t6 p6)                         \
    {                                                                                                                                       \
        aos_future_t *future = aos_future_alloc(config, sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6));   \
        if (!future)                                                                                                                        \
            return NULL;                                                                                                                    \
        memcpy(future->args, &p1, sizeof(t1));                                                                                              \
        memcpy(future->args + sizeof(t1), &p2, sizeof(t2));                                                                                 \
        memcpy(future->args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                                                    \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                                                       \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4), &p5, sizeof(t5));                                          \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5), &p6, sizeof(t6));                             \
        return future;                                                                                                                      \
    }                                                                                                                                       \
    aos_future_t *fn_name##_awaitable_alloc(t1 p1, t2 p2, t3 p3, t4 p4, t5 p5, t6 p6)                                                     \
    {                                                                                                                                       \
        aos_future_t *future = aos_awaitable_alloc(sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6));        \
        if (!future)                                                                                                                        \
            return NULL;                                                                                                                    \
        memcpy(future->args, &p1, sizeof(t1));                                                                                              \
        memcpy(future->args + sizeof(t1), &p2, sizeof(t2));                                                                                 \
        memcpy(future->args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                                                    \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                                                       \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4), &p5, sizeof(t5));                                          \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5), &p6, sizeof(t6));                             \
        return future;                                                                                                                      \
    }                                                                                                                                       \
    aos_future_t *fn_name##_forgettable_alloc(t1 p1, t2 p2, t3 p3, t4 p4, t5 p5, t6 p6)                                                   \
    {                                                                                                                                       \
        aos_future_t *future = aos_forgettable_alloc(sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6));      \
        if (!future)                                                                                                                        \
            return NULL;                                                                                                                    \
        memcpy(future->args, &p1, sizeof(t1));                                                                                              \
        memcpy(future->args + sizeof(t1), &p2, sizeof(t2));                                                                                 \
        memcpy(future->args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                                                    \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                                                       \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4), &p5, sizeof(t5));                                          \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5), &p6, sizeof(t6));                             \
        return future;                                                                                                                      \
    }                                                                                                                                       \
    aos_future_t *fn_name##_eventful_alloc(aos_eventful_config_t *config, t1 p1, t2 p2, t3 p3, t4 p4, t5 p5, t6 p6)                     \
    {                                                                                                                                       \
        aos_future_t *future = aos_eventful_alloc(config, sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6)); \
        if (!future)                                                                                                                        \
            return NULL;                                                                                                                    \
        memcpy(future->args, &p1, sizeof(t1));                                                                                              \
        memcpy(future->args + sizeof(t1), &p2, sizeof(t2));                                                                                 \
        memcpy(future->args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                                                    \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                                                       \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4), &p5, sizeof(t5));                                          \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5), &p6, sizeof(t6));                             \
        return future;                                                                                                                      \
    }
#define _AOS_DEFINE_7(fn_name, t1, t2, t3, t4, t5, t6, t7)                                                                                             \
    aos_future_t *fn_name##_future_alloc(aos_future_config_t *config, t1 p1, t2 p2, t3 p3, t4 p4, t5 p5, t6 p6, t7 p7)                               \
    {                                                                                                                                                    \
        aos_future_t *future = aos_future_alloc(config, sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6) + sizeof(t7));   \
        if (!future)                                                                                                                                     \
            return NULL;                                                                                                                                 \
        memcpy(future->args, &p1, sizeof(t1));                                                                                                           \
        memcpy(future->args + sizeof(t1), &p2, sizeof(t2));                                                                                              \
        memcpy(future->args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                                                                 \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                                                                    \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4), &p5, sizeof(t5));                                                       \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5), &p6, sizeof(t6));                                          \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6), &p7, sizeof(t7));                             \
        return future;                                                                                                                                   \
    }                                                                                                                                                    \
    aos_future_t *fn_name##_awaitable_alloc(t1 p1, t2 p2, t3 p3, t4 p4, t5 p5, t6 p6, t7 p7)                                                           \
    {                                                                                                                                                    \
        aos_future_t *future = aos_awaitable_alloc(sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6) + sizeof(t7));        \
        if (!future)                                                                                                                                     \
            return NULL;                                                                                                                                 \
        memcpy(future->args, &p1, sizeof(t1));                                                                                                           \
        memcpy(future->args + sizeof(t1), &p2, sizeof(t2));                                                                                              \
        memcpy(future->args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                                                                 \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                                                                    \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4), &p5, sizeof(t5));                                                       \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5), &p6, sizeof(t6));                                          \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6), &p7, sizeof(t7));                             \
        return future;                                                                                                                                   \
    }                                                                                                                                                    \
    aos_future_t *fn_name##_forgettable_alloc(t1 p1, t2 p2, t3 p3, t4 p4, t5 p5, t6 p6, t7 p7)                                                         \
    {                                                                                                                                                    \
        aos_future_t *future = aos_forgettable_alloc(sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6) + sizeof(t7));      \
        if (!future)                                                                                                                                     \
            return NULL;                                                                                                                                 \
        memcpy(future->args, &p1, sizeof(t1));                                                                                                           \
        memcpy(future->args + sizeof(t1), &p2, sizeof(t2));                                                                                              \
        memcpy(future->args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                                                                 \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                                                                    \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4), &p5, sizeof(t5));                                                       \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5), &p6, sizeof(t6));                                          \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6), &p7, sizeof(t7));                             \
        return future;                                                                                                                                   \
    }                                                                                                                                                    \
    aos_future_t *fn_name##_eventful_alloc(aos_eventful_config_t *config, t1 p1, t2 p2, t3 p3, t4 p4, t5 p5, t6 p6, t7 p7)                           \
    {                                                                                                                                                    \
        aos_future_t *future = aos_eventful_alloc(config, sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6) + sizeof(t7)); \
        if (!future)                                                                                                                                     \
            return NULL;                                                                                                                                 \
        memcpy(future->args, &p1, sizeof(t1));                                                                                                           \
        memcpy(future->args + sizeof(t1), &p2, sizeof(t2));                                                                                              \
        memcpy(future->args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                                                                 \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                                                                    \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4), &p5, sizeof(t5));                                                       \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5), &p6, sizeof(t6));                                          \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6), &p7, sizeof(t7));                             \
        return future;                                                                                                                                   \
    }
#define _AOS_DEFINE_8(fn_name, t1, t2, t3, t4, t5, t6, t7, t8)                                                                                                      \
    aos_future_t *fn_name##_future_alloc(aos_future_config_t *config, t1 p1, t2 p2, t3 p3, t4 p4, t5 p5, t6 p6, t7 p7, t8 p8)                                     \
    {                                                                                                                                                                 \
        aos_future_t *future = aos_future_alloc(config, sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6) + sizeof(t7) + sizeof(t8));   \
        if (!future)                                                                                                                                                  \
            return NULL;                                                                                                                                              \
        memcpy(future->args, &p1, sizeof(t1));                                                                                                                        \
        memcpy(future->args + sizeof(t1), &p2, sizeof(t2));                                                                                                           \
        memcpy(future->args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                                                                              \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                                                                                 \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4), &p5, sizeof(t5));                                                                    \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5), &p6, sizeof(t6));                                                       \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6), &p7, sizeof(t7));                                          \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6) + sizeof(t7), &p8, sizeof(t8));                             \
        return future;                                                                                                                                                \
    }                                                                                                                                                                 \
    aos_future_t *fn_name##_awaitable_alloc(t1 p1, t2 p2, t3 p3, t4 p4, t5 p5, t6 p6, t7 p7, t8 p8)                                                                 \
    {                                                                                                                                                                 \
        aos_future_t *future = aos_awaitable_alloc(sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6) + sizeof(t7) + sizeof(t8));        \
        if (!future)                                                                                                                                                  \
            return NULL;                                                                                                                                              \
        memcpy(future->args, &p1, sizeof(t1));                                                                                                                        \
        memcpy(future->args + sizeof(t1), &p2, sizeof(t2));                                                                                                           \
        memcpy(future->args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                                                                              \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                                                                                 \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4), &p5, sizeof(t5));                                                                    \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5), &p6, sizeof(t6));                                                       \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6), &p7, sizeof(t7));                                          \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6) + sizeof(t7), &p8, sizeof(t8));                             \
        return future;                                                                                                                                                \
    }                                                                                                                                                                 \
    aos_future_t *fn_name##_forgettable_alloc(t1 p1, t2 p2, t3 p3, t4 p4, t5 p5, t6 p6, t7 p7, t8 p8)                                                               \
    {                                                                                                                                                                 \
        aos_future_t *future = aos_forgettable_alloc(sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6) + sizeof(t7) + sizeof(t8));      \
        if (!future)                                                                                                                                                  \
            return NULL;                                                                                                                                              \
        memcpy(future->args, &p1, sizeof(t1));                                                                                                                        \
        memcpy(future->args + sizeof(t1), &p2, sizeof(t2));                                                                                                           \
        memcpy(future->args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                                                                              \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                                                                                 \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4), &p5, sizeof(t5));                                                                    \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5), &p6, sizeof(t6));                                                       \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6), &p7, sizeof(t7));                                          \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6) + sizeof(t7), &p8, sizeof(t8));                             \
        return future;                                                                                                                                                \
    }                                                                                                                                                                 \
    aos_future_t *fn_name##_eventful_alloc(aos_eventful_config_t *config, t1 p1, t2 p2, t3 p3, t4 p4, t5 p5, t6 p6, t7 p7, t8 p8)                                 \
    {                                                                                                                                                                 \
        aos_future_t *future = aos_eventful_alloc(config, sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6) + sizeof(t7) + sizeof(t8)); \
        if (!future)                                                                                                                                                  \
            return NULL;                                                                                                                                              \
        memcpy(future->args, &p1, sizeof(t1));                                                                                                                        \
        memcpy(future->args + sizeof(t1), &p2, sizeof(t2));                                                                                                           \
        memcpy(future->args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                                                                              \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                                                                                 \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4), &p5, sizeof(t5));                                                                    \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5), &p6, sizeof(t6));                                                       \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6), &p7, sizeof(t7));                                          \
        memcpy(future->args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6) + sizeof(t7), &p8, sizeof(t8));                             \
        return future;                                                                                                                                                \
    }

#define _AOS_DEFINE(fn_name, ...)            \
    _AOS_MACRO_SELECTOR(NULL, ##__VA_ARGS__, \
                          _AOS_DEFINE_8,     \
                          _AOS_DEFINE_7,     \
                          _AOS_DEFINE_6,     \
                          _AOS_DEFINE_5,     \
                          _AOS_DEFINE_4,     \
                          _AOS_DEFINE_3,     \
                          _AOS_DEFINE_2,     \
                          _AOS_DEFINE_1,     \
                          _AOS_DEFINE_0)     \
    (fn_name, ##__VA_ARGS__)

// FIXME: Does the following work? If not we have to revert to the approach used in _AOS_CB_ARGS_ALLOC
// IF IT DOES WORK, WE CAN ALSO DEPRECATE THE declared SUPPORT VARIABLE, WHICH WOULD BE GREAT
// #define _AOS_ARGS_ALLOC(fn_name) (sizeof(fn_name##_fn_args_t) != 0 ? calloc(1, sizeof(fn_name##_fn_args_t)) : NULL)
// #define _AOS_CB_ARGS_ALLOC(cb_name) (sizeof(cb_name##_cb_args_declared) == sizeof(AOS_DECLARED_T) ? calloc(1, sizeof(cb_name##_cb_args_t)) : NULL)

// #define _AOS_ARGS_GET(fn_name, future) ((fn_name##_fn_args_t *)aos_fn_args_get(future))
// #define _AOS_CB_ARGS_GET(cb_name, future) ((cb_name##_cb_args_t *)aos_cb_args_get(future))

// #define _AOS_AWAIT_0P(fn_name) aos_await_0p(fn_name)
// #define _AOS_AWAIT_1P(fn_name, p1) aos_await_1p(fn_name, &p1, sizeof(p1))
// #define _AOS_AWAIT_2P(fn_name, p1, p2) aos_await_2p(fn_name, &p1, sizeof(p1), &p2, sizeof(p2))
// #define _AOS_AWAIT_3P(fn_name, p1, p2, p3) aos_await_3p(fn_name, &p1, sizeof(p1), &p2, sizeof(p2), &p3, sizeof(p3))
// #define _AOS_AWAIT_4P(fn_name, p1, p2, p3, p4) aos_await_4p(fn_name, &p1, sizeof(p1), &p2, sizeof(p2), &p3, sizeof(p3), &p4, sizeof(p4))
// #define _AOS_AWAIT_5P(fn_name, p1, p2, p3, p4, p5) aos_await_5p(fn_name, &p1, sizeof(p1), &p2, sizeof(p2), &p3, sizeof(p3), &p4, sizeof(p4), &p5, sizeof(p5))
// #define _AOS_AWAIT_6P(fn_name, p1, p2, p3, p4, p5, p6) aos_await_6p(fn_name, &p1, sizeof(p1), &p2, sizeof(p2), &p3, sizeof(p3), &p4, sizeof(p4), &p5, sizeof(p5), &p6, sizeof(p6))
// #define _AOS_AWAIT_7P(fn_name, p1, p2, p3, p4, p5, p6, p7) aos_await_7p(fn_name, &p1, sizeof(p1), &p2, sizeof(p2), &p3, sizeof(p3), &p4, sizeof(p4), &p5, sizeof(p5), &p6, sizeof(p6), &p7, sizeof(p7))
// #define _AOS_AWAIT_8P(fn_name, p1, p2, p3, p4, p5, p6, p7, p8) aos_await_8p(fn_name, &p1, sizeof(p1), &p2, sizeof(p2), &p3, sizeof(p3), &p4, sizeof(p4), &p5, sizeof(p5), &p6, sizeof(p6), &p7, sizeof(p7), &p8, sizeof(p8))
// #define _AOS_AWAIT_9P(fn_name, p1, p2, p3, p4, p5, p6, p7, p8, p9) aos_await_9p(fn_name, &p1, sizeof(p1), &p2, sizeof(p2), &p3, sizeof(p3), &p4, sizeof(p4), &p5, sizeof(p5), &p6, sizeof(p6), &p7, sizeof(p7), &p8, sizeof(p8), &p9, sizeof(p9))

// #define _AOS_AWAIT(fn_name, ...)             \
//     _AOS_MACRO_SELECTOR(NULL, ##__VA_ARGS__, \
//                           _AOS_AWAIT_0P,     \
//                           _AOS_AWAIT_1P,     \
//                           _AOS_AWAIT_2P,     \
//                           _AOS_AWAIT_3P,     \
//                           _AOS_AWAIT_4P,     \
//                           _AOS_AWAIT_5P,     \
//                           _AOS_AWAIT_6P,     \
//                           _AOS_AWAIT_7P,     \
//                           _AOS_AWAIT_8P,     \
//                           _AOS_AWAIT_9P)     \
//     (fn_name, ##__VA_ARGS__)

/**
 * @brief These functions allocate the awaitable future and fill its fn_args field with copies of the passed data
 *
 */
// #define _AOS_FUTURE_AWAITABLE_ALLOC_0P(fn_name) aos_alloc_awaitable_0p()
// #define _AOS_FUTURE_AWAITABLE_ALLOC_1P(fn_name, p1) aos_alloc_awaitable_1p(&p1, sizeof(p1))
// #define _AOS_FUTURE_AWAITABLE_ALLOC_2P(fn_name, p1, p2) aos_alloc_awaitable_2p(&p1, sizeof(p1), &p2, sizeof(p2))
// #define _AOS_FUTURE_AWAITABLE_ALLOC_3P(fn_name, p1, p2, p3) aos_alloc_awaitable_3p(&p1, sizeof(p1), &p2, sizeof(p2), &p3, sizeof(p3))
// #define _AOS_FUTURE_AWAITABLE_ALLOC_4P(fn_name, p1, p2, p3, p4) aos_alloc_awaitable_4p(&p1, sizeof(p1), &p2, sizeof(p2), &p3, sizeof(p3), &p4, sizeof(p4))
// #define _AOS_FUTURE_AWAITABLE_ALLOC_5P(fn_name, p1, p2, p3, p4, p5) aos_alloc_awaitable_5p(&p1, sizeof(p1), &p2, sizeof(p2), &p3, sizeof(p3), &p4, sizeof(p4), &p5, sizeof(p5))
// #define _AOS_FUTURE_AWAITABLE_ALLOC_6P(fn_name, p1, p2, p3, p4, p5, p6) aos_alloc_awaitable_6p(&p1, sizeof(p1), &p2, sizeof(p2), &p3, sizeof(p3), &p4, sizeof(p4), &p5, sizeof(p5), &p6, sizeof(p6))
// #define _AOS_FUTURE_AWAITABLE_ALLOC_7P(fn_name, p1, p2, p3, p4, p5, p6, p7) aos_alloc_awaitable_7p(&p1, sizeof(p1), &p2, sizeof(p2), &p3, sizeof(p3), &p4, sizeof(p4), &p5, sizeof(p5), &p6, sizeof(p6), &p7, sizeof(p7))
// #define _AOS_FUTURE_AWAITABLE_ALLOC_8P(fn_name, p1, p2, p3, p4, p5, p6, p7, p8) aos_alloc_awaitable_8p(&p1, sizeof(p1), &p2, sizeof(p2), &p3, sizeof(p3), &p4, sizeof(p4), &p5, sizeof(p5), &p6, sizeof(p6), &p7, sizeof(p7), &p8, sizeof(p8))
// #define _AOS_FUTURE_AWAITABLE_ALLOC_9P(fn_name, p1, p2, p3, p4, p5, p6, p7, p8, p9) aos_alloc_awaitable_9p(&p1, sizeof(p1), &p2, sizeof(p2), &p3, sizeof(p3), &p4, sizeof(p4), &p5, sizeof(p5), &p6, sizeof(p6), &p7, sizeof(p7), &p8, sizeof(p8), &p9, sizeof(p9))

// #define _AOS_FUTURE_AWAITABLE_ALLOC(fn_name, ...)         \
//     _AOS_MACRO_SELECTOR(NULL, ##__VA_ARGS__,              \
//                           _AOS_FUTURE_AWAITABLE_ALLOC_0P, \
//                           _AOS_FUTURE_AWAITABLE_ALLOC_1P, \
//                           _AOS_FUTURE_AWAITABLE_ALLOC_2P, \
//                           _AOS_FUTURE_AWAITABLE_ALLOC_3P, \
//                           _AOS_FUTURE_AWAITABLE_ALLOC_4P, \
//                           _AOS_FUTURE_AWAITABLE_ALLOC_5P, \
//                           _AOS_FUTURE_AWAITABLE_ALLOC_6P, \
//                           _AOS_FUTURE_AWAITABLE_ALLOC_7P, \
//                           _AOS_FUTURE_AWAITABLE_ALLOC_8P, \
//                           _AOS_FUTURE_AWAITABLE_ALLOC_9P) \
//     (fn_name, ##__VA_ARGS__)
// #define _AOS_FUTURE_AWAITABLE_ALLOC(fn_name, ...) aos_awaitable_alloc_##fn_name##_fn(##__VA_ARGS__)

// #define _AOS_FUTURE_AWAITABLE_ALLOC(fn_name) aos_alloc_awaitable(sizeof(fn_name##_fn_args_declared) == sizeof(AOS_DECLARED_T) ? sizeof(fn_name##_fn_args_t) : 0)
// #define _AOS_ALLOC_CALLBACKER(cb_name, fn_name) aos_alloc_callbacker(cb_name, sizeof(cb_name##_cb_args_declared) == sizeof(AOS_DECLARED_T) ? sizeof(cb_name##_cb_args_t) : 0, sizeof(fn_name##_fn_args_declared) == sizeof(AOS_DECLARED_T) ? sizeof(fn_name##_fn_args_t) : 0)
