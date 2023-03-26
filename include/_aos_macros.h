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
#include <aos_future_awaitable.h>
#include <aos_future_forgettable.h>
#include <aos_future_eventful.h>
#include <string.h>

#define _AOS_ARGS_T(fn_name) fn_name##_args_t
#define _AOS_FUTURE_ALLOC_T(fn_name) fn_name##_future_alloc
#define _AOS_AWAITABLE_ALLOC_T(fn_name) fn_name##_awaitable_alloc
#define _AOS_FORGETTABLE_ALLOC_T(fn_name) fn_name##_forgettable_alloc
#define _AOS_EVENTFUL_ALLOC_T(fn_name) fn_name##_eventful_alloc

#define _AOS_MACRO_SELECTOR(a, b, c, d, e, f, g, h, i, N, ...) N

#define _AOS_DECLARE_0(fn_name)                                        \
    typedef struct fn_name##_args_t                                    \
    {                                                                  \
    } fn_name##_args_t;                                                \
    aos_future_t *fn_name##_future_alloc(aos_future_config_t *config); \
    aos_future_t *fn_name##_awaitable_alloc();                         \
    aos_future_t *fn_name##_forgettable_alloc();                       \
    aos_future_t *fn_name##_eventful_alloc(aos_eventful_config_t *config);
#define _AOS_DECLARE_1(fn_name, p1)                                        \
    typedef struct fn_name##_args_t                                        \
    {                                                                      \
        p1;                                                                \
    } fn_name##_args_t;                                                    \
    aos_future_t *fn_name##_future_alloc(aos_future_config_t *config, p1); \
    aos_future_t *fn_name##_awaitable_alloc(p1);                           \
    aos_future_t *fn_name##_forgettable_alloc(p1);                         \
    aos_future_t *fn_name##_eventful_alloc(aos_eventful_config_t *config, p1);
#define _AOS_DECLARE_2(fn_name, p1, p2)                                        \
    typedef struct fn_name##_args_t                                            \
    {                                                                          \
        p1;                                                                    \
        p2;                                                                    \
    } fn_name##_args_t;                                                        \
    aos_future_t *fn_name##_future_alloc(aos_future_config_t *config, p1, p2); \
    aos_future_t *fn_name##_awaitable_alloc(p1, p2);                           \
    aos_future_t *fn_name##_forgettable_alloc(p1, p2);                         \
    aos_future_t *fn_name##_eventful_alloc(aos_eventful_config_t *config, p1, p2);
#define _AOS_DECLARE_3(fn_name, p1, p2, p3)                                        \
    typedef struct fn_name##_args_t                                                \
    {                                                                              \
        p1;                                                                        \
        p2;                                                                        \
        p3;                                                                        \
    } fn_name##_args_t;                                                            \
    aos_future_t *fn_name##_future_alloc(aos_future_config_t *config, p1, p2, p3); \
    aos_future_t *fn_name##_awaitable_alloc(p1, p2, p3);                           \
    aos_future_t *fn_name##_forgettable_alloc(p1, p2, p3);                         \
    aos_future_t *fn_name##_eventful_alloc(aos_eventful_config_t *config, p1, p2, p3);
#define _AOS_DECLARE_4(fn_name, p1, p2, p3, p4)                                        \
    typedef struct fn_name##_args_t                                                    \
    {                                                                                  \
        p1;                                                                            \
        p2;                                                                            \
        p3;                                                                            \
        p4;                                                                            \
    } fn_name##_args_t;                                                                \
    aos_future_t *fn_name##_future_alloc(aos_future_config_t *config, p1, p2, p3, p4); \
    aos_future_t *fn_name##_awaitable_alloc(p1, p2, p3, p4);                           \
    aos_future_t *fn_name##_forgettable_alloc(p1, p2, p3, p4);                         \
    aos_future_t *fn_name##_eventful_alloc(aos_eventful_config_t *config, p1, p2, p3, p4);
#define _AOS_DECLARE_5(fn_name, p1, p2, p3, p4, p5)                                        \
    typedef struct fn_name##_args_t                                                        \
    {                                                                                      \
        p1;                                                                                \
        p2;                                                                                \
        p3;                                                                                \
        p4;                                                                                \
        p5;                                                                                \
    } fn_name##_args_t;                                                                    \
    aos_future_t *fn_name##_future_alloc(aos_future_config_t *config, p1, p2, p3, p4, p5); \
    aos_future_t *fn_name##_awaitable_alloc(p1, p2, p3, p4, p5);                           \
    aos_future_t *fn_name##_forgettable_alloc(p1, p2, p3, p4, p5);                         \
    aos_future_t *fn_name##_eventful_alloc(aos_eventful_config_t *config, p1, p2, p3, p4, p5);
#define _AOS_DECLARE_6(fn_name, p1, p2, p3, p4, p5, p6)                                        \
    typedef struct fn_name##_args_t                                                            \
    {                                                                                          \
        p1;                                                                                    \
        p2;                                                                                    \
        p3;                                                                                    \
        p4;                                                                                    \
        p5;                                                                                    \
        p6;                                                                                    \
    } fn_name##_args_t;                                                                        \
    aos_future_t *fn_name##_future_alloc(aos_future_config_t *config, p1, p2, p3, p4, p5, p6); \
    aos_future_t *fn_name##_awaitable_alloc(p1, p2, p3, p4, p5, p6);                           \
    aos_future_t *fn_name##_forgettable_alloc(p1, p2, p3, p4, p5, p6);                         \
    aos_future_t *fn_name##_eventful_alloc(aos_eventful_config_t *config, p1, p2, p3, p4, p5, p6);
#define _AOS_DECLARE_7(fn_name, p1, p2, p3, p4, p5, p6, p7)                                        \
    typedef struct fn_name##_args_t                                                                \
    {                                                                                              \
        p1;                                                                                        \
        p2;                                                                                        \
        p3;                                                                                        \
        p4;                                                                                        \
        p5;                                                                                        \
        p6;                                                                                        \
        p7;                                                                                        \
    } fn_name##_args_t;                                                                            \
    aos_future_t *fn_name##_future_alloc(aos_future_config_t *config, p1, p2, p3, p4, p5, p6, p7); \
    aos_future_t *fn_name##_awaitable_alloc(p1, p2, p3, p4, p5, p6, p7);                           \
    aos_future_t *fn_name##_forgettable_alloc(p1, p2, p3, p4, p5, p6, p7);                         \
    aos_future_t *fn_name##_eventful_alloc(aos_eventful_config_t *config, p1, p2, p3, p4, p5, p6, p7);
#define _AOS_DECLARE_8(fn_name, p1, p2, p3, p4, p5, p6, p7, p8)                                        \
    typedef struct fn_name##_args_t                                                                    \
    {                                                                                                  \
        p1;                                                                                            \
        p2;                                                                                            \
        p3;                                                                                            \
        p4;                                                                                            \
        p5;                                                                                            \
        p6;                                                                                            \
        p7;                                                                                            \
        p8;                                                                                            \
    } fn_name##_args_t;                                                                                \
    aos_future_t *fn_name##_future_alloc(aos_future_config_t *config, p1, p2, p3, p4, p5, p6, p7, p8); \
    aos_future_t *fn_name##_awaitable_alloc(p1, p2, p3, p4, p5, p6, p7, p8);                           \
    aos_future_t *fn_name##_forgettable_alloc(p1, p2, p3, p4, p5, p6, p7, p8);                         \
    aos_future_t *fn_name##_eventful_alloc(aos_eventful_config_t *config, p1, p2, p3, p4, p5, p6, p7, p8);

#define _AOS_DECLARE(fn_name, ...)           \
    _AOS_MACRO_SELECTOR(NULL, ##__VA_ARGS__, \
                        _AOS_DECLARE_8,      \
                        _AOS_DECLARE_7,      \
                        _AOS_DECLARE_6,      \
                        _AOS_DECLARE_5,      \
                        _AOS_DECLARE_4,      \
                        _AOS_DECLARE_3,      \
                        _AOS_DECLARE_2,      \
                        _AOS_DECLARE_1,      \
                        _AOS_DECLARE_0)      \
    (fn_name, ##__VA_ARGS__)

#define _AOS_DEFINE_0(fn_name)                                            \
    aos_future_t *fn_name##_future_alloc(aos_future_config_t *config)     \
    {                                                                     \
        return aos_future_alloc(config, 0);                               \
    }                                                                     \
    aos_future_t *fn_name##_awaitable_alloc()                             \
    {                                                                     \
        return aos_awaitable_alloc(0);                                    \
    }                                                                     \
    aos_future_t *fn_name##_forgettable_alloc()                           \
    {                                                                     \
        return aos_forgettable_alloc(0);                                  \
    }                                                                     \
    aos_future_t *fn_name##_eventful_alloc(aos_eventful_config_t *config) \
    {                                                                     \
        return aos_eventful_alloc(config, 0);                             \
    }
#define _AOS_DEFINE_1(fn_name, t1)                                               \
    aos_future_t *fn_name##_future_alloc(aos_future_config_t *config, t1 p1)     \
    {                                                                            \
        aos_future_t *future = aos_future_alloc(config, sizeof(t1));             \
        if (!future)                                                             \
            return NULL;                                                         \
        void *args = aos_args_get(future);                                       \
        memcpy(args, &p1, sizeof(t1));                                           \
        return future;                                                           \
    }                                                                            \
    aos_future_t *fn_name##_awaitable_alloc(t1 p1)                               \
    {                                                                            \
        aos_future_t *future = aos_awaitable_alloc(sizeof(t1));                  \
        if (!future)                                                             \
            return NULL;                                                         \
        void *args = aos_args_get(future);                                       \
        memcpy(args, &p1, sizeof(t1));                                           \
        return future;                                                           \
    }                                                                            \
    aos_future_t *fn_name##_forgettable_alloc(t1 p1)                             \
    {                                                                            \
        aos_future_t *future = aos_forgettable_alloc(sizeof(t1));                \
        if (!future)                                                             \
            return NULL;                                                         \
        void *args = aos_args_get(future);                                       \
        memcpy(args, &p1, sizeof(t1));                                           \
        return future;                                                           \
    }                                                                            \
    aos_future_t *fn_name##_eventful_alloc(aos_eventful_config_t *config, t1 p1) \
    {                                                                            \
        aos_future_t *future = aos_eventful_alloc(config, sizeof(t1));           \
        if (!future)                                                             \
            return NULL;                                                         \
        void *args = aos_args_get(future);                                       \
        memcpy(args, &p1, sizeof(t1));                                           \
        return future;                                                           \
    }
#define _AOS_DEFINE_2(fn_name, t1, t2)                                                  \
    aos_future_t *fn_name##_future_alloc(aos_future_config_t *config, t1 p1, t2 p2)     \
    {                                                                                   \
        aos_future_t *future = aos_future_alloc(config, sizeof(t1) + sizeof(t2));       \
        if (!future)                                                                    \
            return NULL;                                                                \
        void *args = aos_args_get(future);                                              \
        memcpy(args, &p1, sizeof(t1));                                                  \
        memcpy(args + sizeof(t1), &p2, sizeof(t2));                                     \
        return future;                                                                  \
    }                                                                                   \
    aos_future_t *fn_name##_awaitable_alloc(t1 p1, t2 p2)                               \
    {                                                                                   \
        aos_future_t *future = aos_awaitable_alloc(sizeof(t1) + sizeof(t2));            \
        if (!future)                                                                    \
            return NULL;                                                                \
        void *args = aos_args_get(future);                                              \
        memcpy(args, &p1, sizeof(t1));                                                  \
        memcpy(args + sizeof(t1), &p2, sizeof(t2));                                     \
        return future;                                                                  \
    }                                                                                   \
    aos_future_t *fn_name##_forgettable_alloc(t1 p1, t2 p2)                             \
    {                                                                                   \
        aos_future_t *future = aos_forgettable_alloc(sizeof(t1) + sizeof(t2));          \
        if (!future)                                                                    \
            return NULL;                                                                \
        void *args = aos_args_get(future);                                              \
        memcpy(args, &p1, sizeof(t1));                                                  \
        memcpy(args + sizeof(t1), &p2, sizeof(t2));                                     \
        return future;                                                                  \
    }                                                                                   \
    aos_future_t *fn_name##_eventful_alloc(aos_eventful_config_t *config, t1 p1, t2 p2) \
    {                                                                                   \
        aos_future_t *future = aos_eventful_alloc(config, sizeof(t1) + sizeof(t2));     \
        if (!future)                                                                    \
            return NULL;                                                                \
        void *args = aos_args_get(future);                                              \
        memcpy(args, &p1, sizeof(t1));                                                  \
        memcpy(args + sizeof(t1), &p2, sizeof(t2));                                     \
        return future;                                                                  \
    }
#define _AOS_DEFINE_3(fn_name, t1, t2, t3)                                                       \
    aos_future_t *fn_name##_future_alloc(aos_future_config_t *config, t1 p1, t2 p2, t3 p3)       \
    {                                                                                            \
        aos_future_t *future = aos_future_alloc(config, sizeof(t1) + sizeof(t2) + sizeof(t3));   \
        if (!future)                                                                             \
            return NULL;                                                                         \
        void *args = aos_args_get(future);                                                       \
        memcpy(args, &p1, sizeof(t1));                                                           \
        memcpy(args + sizeof(t1), &p2, sizeof(t2));                                              \
        memcpy(args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                 \
        return future;                                                                           \
    }                                                                                            \
    aos_future_t *fn_name##_awaitable_alloc(t1 p1, t2 p2, t3 p3)                                 \
    {                                                                                            \
        aos_future_t *future = aos_awaitable_alloc(sizeof(t1) + sizeof(t2) + sizeof(t3));        \
        if (!future)                                                                             \
            return NULL;                                                                         \
        void *args = aos_args_get(future);                                                       \
        memcpy(args, &p1, sizeof(t1));                                                           \
        memcpy(args + sizeof(t1), &p2, sizeof(t2));                                              \
        memcpy(args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                 \
        return future;                                                                           \
    }                                                                                            \
    aos_future_t *fn_name##_forgettable_alloc(t1 p1, t2 p2, t3 p3)                               \
    {                                                                                            \
        aos_future_t *future = aos_forgettable_alloc(sizeof(t1) + sizeof(t2) + sizeof(t3));      \
        if (!future)                                                                             \
            return NULL;                                                                         \
        void *args = aos_args_get(future);                                                       \
        memcpy(args, &p1, sizeof(t1));                                                           \
        memcpy(args + sizeof(t1), &p2, sizeof(t2));                                              \
        memcpy(args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                 \
        return future;                                                                           \
    }                                                                                            \
    aos_future_t *fn_name##_eventful_alloc(aos_eventful_config_t *config, t1 p1, t2 p2, t3 p3)   \
    {                                                                                            \
        aos_future_t *future = aos_eventful_alloc(config, sizeof(t1) + sizeof(t2) + sizeof(t3)); \
        if (!future)                                                                             \
            return NULL;                                                                         \
        void *args = aos_args_get(future);                                                       \
        memcpy(args, &p1, sizeof(t1));                                                           \
        memcpy(args + sizeof(t1), &p2, sizeof(t2));                                              \
        memcpy(args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                 \
        return future;                                                                           \
    }
#define _AOS_DEFINE_4(fn_name, t1, t2, t3, t4)                                                                \
    aos_future_t *fn_name##_future_alloc(aos_future_config_t *config, t1 p1, t2 p2, t3 p3, t4 p4)             \
    {                                                                                                         \
        aos_future_t *future = aos_future_alloc(config, sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4));   \
        if (!future)                                                                                          \
            return NULL;                                                                                      \
        void *args = aos_args_get(future);                                                                    \
        memcpy(args, &p1, sizeof(t1));                                                                        \
        memcpy(args + sizeof(t1), &p2, sizeof(t2));                                                           \
        memcpy(args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                              \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                                 \
        return future;                                                                                        \
    }                                                                                                         \
    aos_future_t *fn_name##_awaitable_alloc(t1 p1, t2 p2, t3 p3, t4 p4)                                       \
    {                                                                                                         \
        aos_future_t *future = aos_awaitable_alloc(sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4));        \
        if (!future)                                                                                          \
            return NULL;                                                                                      \
        void *args = aos_args_get(future);                                                                    \
        memcpy(args, &p1, sizeof(t1));                                                                        \
        memcpy(args + sizeof(t1), &p2, sizeof(t2));                                                           \
        memcpy(args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                              \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                                 \
        return future;                                                                                        \
    }                                                                                                         \
    aos_future_t *fn_name##_forgettable_alloc(t1 p1, t2 p2, t3 p3, t4 p4)                                     \
    {                                                                                                         \
        aos_future_t *future = aos_forgettable_alloc(sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4));      \
        if (!future)                                                                                          \
            return NULL;                                                                                      \
        void *args = aos_args_get(future);                                                                    \
        memcpy(args, &p1, sizeof(t1));                                                                        \
        memcpy(args + sizeof(t1), &p2, sizeof(t2));                                                           \
        memcpy(args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                              \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                                 \
        return future;                                                                                        \
    }                                                                                                         \
    aos_future_t *fn_name##_eventful_alloc(aos_eventful_config_t *config, t1 p1, t2 p2, t3 p3, t4 p4)         \
    {                                                                                                         \
        aos_future_t *future = aos_eventful_alloc(config, sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4)); \
        if (!future)                                                                                          \
            return NULL;                                                                                      \
        void *args = aos_args_get(future);                                                                    \
        memcpy(args, &p1, sizeof(t1));                                                                        \
        memcpy(args + sizeof(t1), &p2, sizeof(t2));                                                           \
        memcpy(args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                              \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                                 \
        return future;                                                                                        \
    }
#define _AOS_DEFINE_5(fn_name, t1, t2, t3, t4, t5)                                                                         \
    aos_future_t *fn_name##_future_alloc(aos_future_config_t *config, t1 p1, t2 p2, t3 p3, t4 p4, t5 p5)                   \
    {                                                                                                                      \
        aos_future_t *future = aos_future_alloc(config, sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5));   \
        if (!future)                                                                                                       \
            return NULL;                                                                                                   \
        void *args = aos_args_get(future);                                                                                 \
        memcpy(args, &p1, sizeof(t1));                                                                                     \
        memcpy(args + sizeof(t1), &p2, sizeof(t2));                                                                        \
        memcpy(args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                                           \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                                              \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4), &p5, sizeof(t5));                                 \
        return future;                                                                                                     \
    }                                                                                                                      \
    aos_future_t *fn_name##_awaitable_alloc(t1 p1, t2 p2, t3 p3, t4 p4, t5 p5)                                             \
    {                                                                                                                      \
        aos_future_t *future = aos_awaitable_alloc(sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5));        \
        if (!future)                                                                                                       \
            return NULL;                                                                                                   \
        void *args = aos_args_get(future);                                                                                 \
        memcpy(args, &p1, sizeof(t1));                                                                                     \
        memcpy(args + sizeof(t1), &p2, sizeof(t2));                                                                        \
        memcpy(args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                                           \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                                              \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4), &p5, sizeof(t5));                                 \
        return future;                                                                                                     \
    }                                                                                                                      \
    aos_future_t *fn_name##_forgettable_alloc(t1 p1, t2 p2, t3 p3, t4 p4, t5 p5)                                           \
    {                                                                                                                      \
        aos_future_t *future = aos_forgettable_alloc(sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5));      \
        if (!future)                                                                                                       \
            return NULL;                                                                                                   \
        void *args = aos_args_get(future);                                                                                 \
        memcpy(args, &p1, sizeof(t1));                                                                                     \
        memcpy(args + sizeof(t1), &p2, sizeof(t2));                                                                        \
        memcpy(args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                                           \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                                              \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4), &p5, sizeof(t5));                                 \
        return future;                                                                                                     \
    }                                                                                                                      \
    aos_future_t *fn_name##_eventful_alloc(aos_eventful_config_t *config, t1 p1, t2 p2, t3 p3, t4 p4, t5 p5)               \
    {                                                                                                                      \
        aos_future_t *future = aos_eventful_alloc(config, sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5)); \
        if (!future)                                                                                                       \
            return NULL;                                                                                                   \
        void *args = aos_args_get(future);                                                                                 \
        memcpy(args, &p1, sizeof(t1));                                                                                     \
        memcpy(args + sizeof(t1), &p2, sizeof(t2));                                                                        \
        memcpy(args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                                           \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                                              \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4), &p5, sizeof(t5));                                 \
        return future;                                                                                                     \
    }
#define _AOS_DEFINE_6(fn_name, t1, t2, t3, t4, t5, t6)                                                                                  \
    aos_future_t *fn_name##_future_alloc(aos_future_config_t *config, t1 p1, t2 p2, t3 p3, t4 p4, t5 p5, t6 p6)                         \
    {                                                                                                                                   \
        aos_future_t *future = aos_future_alloc(config, sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6));   \
        if (!future)                                                                                                                    \
            return NULL;                                                                                                                \
        void *args = aos_args_get(future);                                                                                              \
        memcpy(args, &p1, sizeof(t1));                                                                                                  \
        memcpy(args + sizeof(t1), &p2, sizeof(t2));                                                                                     \
        memcpy(args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                                                        \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                                                           \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4), &p5, sizeof(t5));                                              \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5), &p6, sizeof(t6));                                 \
        return future;                                                                                                                  \
    }                                                                                                                                   \
    aos_future_t *fn_name##_awaitable_alloc(t1 p1, t2 p2, t3 p3, t4 p4, t5 p5, t6 p6)                                                   \
    {                                                                                                                                   \
        aos_future_t *future = aos_awaitable_alloc(sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6));        \
        if (!future)                                                                                                                    \
            return NULL;                                                                                                                \
        void *args = aos_args_get(future);                                                                                              \
        memcpy(args, &p1, sizeof(t1));                                                                                                  \
        memcpy(args + sizeof(t1), &p2, sizeof(t2));                                                                                     \
        memcpy(args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                                                        \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                                                           \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4), &p5, sizeof(t5));                                              \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5), &p6, sizeof(t6));                                 \
        return future;                                                                                                                  \
    }                                                                                                                                   \
    aos_future_t *fn_name##_forgettable_alloc(t1 p1, t2 p2, t3 p3, t4 p4, t5 p5, t6 p6)                                                 \
    {                                                                                                                                   \
        aos_future_t *future = aos_forgettable_alloc(sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6));      \
        if (!future)                                                                                                                    \
            return NULL;                                                                                                                \
        void *args = aos_args_get(future);                                                                                              \
        memcpy(args, &p1, sizeof(t1));                                                                                                  \
        memcpy(args + sizeof(t1), &p2, sizeof(t2));                                                                                     \
        memcpy(args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                                                        \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                                                           \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4), &p5, sizeof(t5));                                              \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5), &p6, sizeof(t6));                                 \
        return future;                                                                                                                  \
    }                                                                                                                                   \
    aos_future_t *fn_name##_eventful_alloc(aos_eventful_config_t *config, t1 p1, t2 p2, t3 p3, t4 p4, t5 p5, t6 p6)                     \
    {                                                                                                                                   \
        aos_future_t *future = aos_eventful_alloc(config, sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6)); \
        if (!future)                                                                                                                    \
            return NULL;                                                                                                                \
        void *args = aos_args_get(future);                                                                                              \
        memcpy(args, &p1, sizeof(t1));                                                                                                  \
        memcpy(args + sizeof(t1), &p2, sizeof(t2));                                                                                     \
        memcpy(args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                                                        \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                                                           \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4), &p5, sizeof(t5));                                              \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5), &p6, sizeof(t6));                                 \
        return future;                                                                                                                  \
    }
#define _AOS_DEFINE_7(fn_name, t1, t2, t3, t4, t5, t6, t7)                                                                                           \
    aos_future_t *fn_name##_future_alloc(aos_future_config_t *config, t1 p1, t2 p2, t3 p3, t4 p4, t5 p5, t6 p6, t7 p7)                               \
    {                                                                                                                                                \
        aos_future_t *future = aos_future_alloc(config, sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6) + sizeof(t7));   \
        if (!future)                                                                                                                                 \
            return NULL;                                                                                                                             \
        void *args = aos_args_get(future);                                                                                                           \
        memcpy(args, &p1, sizeof(t1));                                                                                                               \
        memcpy(args + sizeof(t1), &p2, sizeof(t2));                                                                                                  \
        memcpy(args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                                                                     \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                                                                        \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4), &p5, sizeof(t5));                                                           \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5), &p6, sizeof(t6));                                              \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6), &p7, sizeof(t7));                                 \
        return future;                                                                                                                               \
    }                                                                                                                                                \
    aos_future_t *fn_name##_awaitable_alloc(t1 p1, t2 p2, t3 p3, t4 p4, t5 p5, t6 p6, t7 p7)                                                         \
    {                                                                                                                                                \
        aos_future_t *future = aos_awaitable_alloc(sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6) + sizeof(t7));        \
        if (!future)                                                                                                                                 \
            return NULL;                                                                                                                             \
        void *args = aos_args_get(future);                                                                                                           \
        memcpy(args, &p1, sizeof(t1));                                                                                                               \
        memcpy(args + sizeof(t1), &p2, sizeof(t2));                                                                                                  \
        memcpy(args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                                                                     \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                                                                        \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4), &p5, sizeof(t5));                                                           \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5), &p6, sizeof(t6));                                              \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6), &p7, sizeof(t7));                                 \
        return future;                                                                                                                               \
    }                                                                                                                                                \
    aos_future_t *fn_name##_forgettable_alloc(t1 p1, t2 p2, t3 p3, t4 p4, t5 p5, t6 p6, t7 p7)                                                       \
    {                                                                                                                                                \
        aos_future_t *future = aos_forgettable_alloc(sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6) + sizeof(t7));      \
        if (!future)                                                                                                                                 \
            return NULL;                                                                                                                             \
        void *args = aos_args_get(future);                                                                                                           \
        memcpy(args, &p1, sizeof(t1));                                                                                                               \
        memcpy(args + sizeof(t1), &p2, sizeof(t2));                                                                                                  \
        memcpy(args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                                                                     \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                                                                        \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4), &p5, sizeof(t5));                                                           \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5), &p6, sizeof(t6));                                              \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6), &p7, sizeof(t7));                                 \
        return future;                                                                                                                               \
    }                                                                                                                                                \
    aos_future_t *fn_name##_eventful_alloc(aos_eventful_config_t *config, t1 p1, t2 p2, t3 p3, t4 p4, t5 p5, t6 p6, t7 p7)                           \
    {                                                                                                                                                \
        aos_future_t *future = aos_eventful_alloc(config, sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6) + sizeof(t7)); \
        if (!future)                                                                                                                                 \
            return NULL;                                                                                                                             \
        void *args = aos_args_get(future);                                                                                                           \
        memcpy(args, &p1, sizeof(t1));                                                                                                               \
        memcpy(args + sizeof(t1), &p2, sizeof(t2));                                                                                                  \
        memcpy(args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                                                                     \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                                                                        \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4), &p5, sizeof(t5));                                                           \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5), &p6, sizeof(t6));                                              \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6), &p7, sizeof(t7));                                 \
        return future;                                                                                                                               \
    }
#define _AOS_DEFINE_8(fn_name, t1, t2, t3, t4, t5, t6, t7, t8)                                                                                                    \
    aos_future_t *fn_name##_future_alloc(aos_future_config_t *config, t1 p1, t2 p2, t3 p3, t4 p4, t5 p5, t6 p6, t7 p7, t8 p8)                                     \
    {                                                                                                                                                             \
        aos_future_t *future = aos_future_alloc(config, sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6) + sizeof(t7) + sizeof(t8));   \
        if (!future)                                                                                                                                              \
            return NULL;                                                                                                                                          \
        void *args = aos_args_get(future);                                                                                                                        \
        memcpy(args, &p1, sizeof(t1));                                                                                                                            \
        memcpy(args + sizeof(t1), &p2, sizeof(t2));                                                                                                               \
        memcpy(args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                                                                                  \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                                                                                     \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4), &p5, sizeof(t5));                                                                        \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5), &p6, sizeof(t6));                                                           \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6), &p7, sizeof(t7));                                              \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6) + sizeof(t7), &p8, sizeof(t8));                                 \
        return future;                                                                                                                                            \
    }                                                                                                                                                             \
    aos_future_t *fn_name##_awaitable_alloc(t1 p1, t2 p2, t3 p3, t4 p4, t5 p5, t6 p6, t7 p7, t8 p8)                                                               \
    {                                                                                                                                                             \
        aos_future_t *future = aos_awaitable_alloc(sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6) + sizeof(t7) + sizeof(t8));        \
        if (!future)                                                                                                                                              \
            return NULL;                                                                                                                                          \
        void *args = aos_args_get(future);                                                                                                                        \
        memcpy(args, &p1, sizeof(t1));                                                                                                                            \
        memcpy(args + sizeof(t1), &p2, sizeof(t2));                                                                                                               \
        memcpy(args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                                                                                  \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                                                                                     \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4), &p5, sizeof(t5));                                                                        \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5), &p6, sizeof(t6));                                                           \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6), &p7, sizeof(t7));                                              \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6) + sizeof(t7), &p8, sizeof(t8));                                 \
        return future;                                                                                                                                            \
    }                                                                                                                                                             \
    aos_future_t *fn_name##_forgettable_alloc(t1 p1, t2 p2, t3 p3, t4 p4, t5 p5, t6 p6, t7 p7, t8 p8)                                                             \
    {                                                                                                                                                             \
        aos_future_t *future = aos_forgettable_alloc(sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6) + sizeof(t7) + sizeof(t8));      \
        if (!future)                                                                                                                                              \
            return NULL;                                                                                                                                          \
        void *args = aos_args_get(future);                                                                                                                        \
        memcpy(args, &p1, sizeof(t1));                                                                                                                            \
        memcpy(args + sizeof(t1), &p2, sizeof(t2));                                                                                                               \
        memcpy(args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                                                                                  \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                                                                                     \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4), &p5, sizeof(t5));                                                                        \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5), &p6, sizeof(t6));                                                           \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6), &p7, sizeof(t7));                                              \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6) + sizeof(t7), &p8, sizeof(t8));                                 \
        return future;                                                                                                                                            \
    }                                                                                                                                                             \
    aos_future_t *fn_name##_eventful_alloc(aos_eventful_config_t *config, t1 p1, t2 p2, t3 p3, t4 p4, t5 p5, t6 p6, t7 p7, t8 p8)                                 \
    {                                                                                                                                                             \
        aos_future_t *future = aos_eventful_alloc(config, sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6) + sizeof(t7) + sizeof(t8)); \
        if (!future)                                                                                                                                              \
            return NULL;                                                                                                                                          \
        void *args = aos_args_get(future);                                                                                                                        \
        memcpy(args, &p1, sizeof(t1));                                                                                                                            \
        memcpy(args + sizeof(t1), &p2, sizeof(t2));                                                                                                               \
        memcpy(args + sizeof(t1) + sizeof(t2), &p3, sizeof(t3));                                                                                                  \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3), &p4, sizeof(t4));                                                                                     \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4), &p5, sizeof(t5));                                                                        \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5), &p6, sizeof(t6));                                                           \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6), &p7, sizeof(t7));                                              \
        memcpy(args + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6) + sizeof(t7), &p8, sizeof(t8));                                 \
        return future;                                                                                                                                            \
    }

#define _AOS_DEFINE(fn_name, ...)            \
    _AOS_MACRO_SELECTOR(NULL, ##__VA_ARGS__, \
                        _AOS_DEFINE_8,       \
                        _AOS_DEFINE_7,       \
                        _AOS_DEFINE_6,       \
                        _AOS_DEFINE_5,       \
                        _AOS_DEFINE_4,       \
                        _AOS_DEFINE_3,       \
                        _AOS_DEFINE_2,       \
                        _AOS_DEFINE_1,       \
                        _AOS_DEFINE_0)       \
    (fn_name, ##__VA_ARGS__)
