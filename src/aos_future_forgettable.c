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

aos_future_t *aos_forgettable_alloc(size_t args_size)
{
    aos_future_t *future = calloc(1, sizeof(aos_future_t));
    void *args = NULL;
    if (!future || (args_size && !(args = calloc(1, args_size))))
    {
        free(future);
        free(args);
        return NULL;
    }
    future->cb = _aos_forgettable_cb;
    future->args = args;
    return future;
}

static void _aos_forgettable_cb(aos_future_t *future)
{
    free(future->args);
    free(future);
}