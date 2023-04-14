/**
 * @file aos_spawn.c
 * @author Michele Riva (michele.riva@protonmail.com)
 * @brief AsyncRTOS spawn implementation
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
#include <aos_spawn.h>
#include <_aos_future.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

struct _aos_spawn_t
{
    unsigned int stacksize;
    unsigned int priority;
    char *name;
};

struct _aos_spawn_ctx_t
{
    void (*fn)(aos_future_t *future);
    aos_future_t *future;
};

static void _aos_spawn_task(void *args);

aos_future_t *aos_spawn(aos_spawn_config_t *config, void (*fn)(aos_future_t *), aos_future_t *future)
{
    struct _aos_spawn_ctx_t *ctx = calloc(1, sizeof(struct _aos_spawn_ctx_t));
    if (!ctx)
    {
        _aos_reject(future);
        return future;
    }
    ctx->fn = fn;
    ctx->future = future;
    if (!xTaskCreate(
            _aos_spawn_task,
            config->name,
            config->stacksize ? config->stacksize : CONFIG_AOS_TASK_STACKSIZEDEFAULT,
            ctx,
            config->priority ? config->priority : CONFIG_AOS_TASK_PRIORITYDEFAULT,
            NULL))
    {
        _aos_reject(future);
        return future;
    }
    return future;
}

static void _aos_spawn_task(void *args)
{
    struct _aos_spawn_ctx_t *ctx = args;
    ctx->fn(ctx->future);
    free(ctx);
    vTaskDelete(NULL);
}