/**
 * @file aos_future_awaitable.c
 * @author Michele Riva (michele.riva@protonmail.com)
 * @brief AsyncRTOS awaitable future implementation
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
#include <_aos_future.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

static void _aos_awaitable_cb(aos_future_t *future)
{
    xSemaphoreGive((SemaphoreHandle_t)future->ctx);
}

aos_future_t *aos_awaitable_alloc(size_t args_size)
{
    aos_future_t *future = calloc(1, sizeof(aos_future_t));
    SemaphoreHandle_t ctx = xSemaphoreCreateBinary();
    void *args = NULL;
    if (!future || !ctx || (args_size && !(args = calloc(1, args_size))))
    {
        free(future);
        vSemaphoreDelete(ctx);
        free(args);
        return NULL;
    }
    future->cb = _aos_awaitable_cb;
    future->ctx = (void *)ctx;
    future->args = args;
    return future;
}

void aos_awaitable_free(aos_future_t *future)
{
    if (future)
    {
        free(future->args);
        vSemaphoreDelete((SemaphoreHandle_t)future->ctx);
        free(future);
    }
}

aos_future_t *aos_await(aos_future_t *future)
{
    xSemaphoreTake((SemaphoreHandle_t)future->ctx, portMAX_DELAY);
    return future;
}
