
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
    void(*fn)(aos_future_t *);
    aos_future_t *future;
};

static void _aos_spawn_task(void *args);

aos_future_t *aos_spawn(aos_spawn_config_t *config, void(*fn)(aos_future_t *), aos_future_t *future)
{
    struct _aos_spawn_ctx_t *ctx = calloc(1, sizeof(struct _aos_spawn_ctx_t));
    if (!ctx)
    {
        _aos_reject(future);;
        return future;
    }
    ctx->fn = fn;
    ctx->future = future;
    if (!xTaskCreate(
            _aos_spawn_task,
            config->name,
            config->stacksize,
            ctx,
            config->priority,
            NULL))
    {
        _aos_reject(future);;
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