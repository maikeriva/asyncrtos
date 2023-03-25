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
#include <_aos_future.h>
#include <stddef.h>

void *aos_args_get(aos_future_t *future)
{
    return future->args;
}

void aos_resolve(aos_future_t *future)
{
    future->state = AOS_STATE_RESOLVED;
    future->cb(future);
}

bool aos_isresolved(aos_future_t *future)
{
    return future->state == AOS_STATE_RESOLVED;
}

aos_future_t *aos_future_alloc(aos_future_config_t *config, size_t args_size)
{
    aos_future_t *future = calloc(1, sizeof(aos_future_t));
    void *args = NULL;
    if (!future || (args_size && !(args = calloc(1, args_size))))
    {
        free(future);
        free(args);
        return NULL;
    }
    future->cb = config->cb;
    future->ctx = config->ctx;
    future->args = args;
    return future;
}

void *aos_future_free(aos_future_t *future)
{
    if (!future)
    {
        return NULL;
    }
    void *ctx = future->ctx;
    free(future->args);
    free(future);
    return ctx;
}
