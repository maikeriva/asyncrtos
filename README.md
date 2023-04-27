# AsyncRTOS

AsyncRTOS is a framework for asynchronous and multithreaded applications built on top of ESP-IDF and potentially other FreeRTOS SMP variants. It is written in pure C and abstracts away the complexity of working on SMP multi-core architectures such as ESP32.

AsyncRTOS allows to create isolated tasks which can float independently on any available core, and communicate safely between them through futures. Similarly to other programming languages (C#, Java, etc.) futures represent the state of an operation, and can be awaited synchronously for their completion or made to asynchronously invoke a callback.

This allows to build firmwares as ecosystems of microservices with deterministic behaviour. When designed right, these services are idempotent and allow for a declarative programming approach.

## Why?

On single-core architectures, FreeRTOS tasks are executed one at a time and switch places according to a priority system. This makes the code flow deterministically and predictably.

On multi-core SMP architectures such as ESP32 however, multiple tasks can be executed at once and thus deterministic execution is not guaranteed anymore. Mutexes or other synchronization mechanisms can be used to restore that, but with the downside of temporarily blocking a task unless some complex logic is introduced.

AsyncRTOS was born to abstract away this complex logic and restore execution determinism through a developer-friendly API.

## How?

AsyncRTOS introduces three essential concepts:

### Futures

Similarly to other programming languages (C#, Java, etc.) futures represent the state of an operation, and can be awaited synchronously for their completion or made to asynchronously invoke a callback or raise a task event.

There are different kinds of future, each with their own API:

- **Awaitable**: Used to wait the completion of an operation synchronously with `aos_await(future)`.
- **Eventful**: Used to be notified asynchronously when an operation completes through a task event.
- **Forgettable**: Used when we want to raise an event in a task and we are not interested in a response.
- **Generic**: Used when we need to define a custom callback to be invoked when an operation completes.

### Asynchronous functions

Asynchronous functions are simply functions which accept futures, and which are marked as completed when their future is resolved with `aos_resolve(future)`. 

### Asynchronous tasks

AsyncRTOS tasks communicate between them by exchanging messages carrying futures. Sending tasks can then either synchronously wait for a response by awaiting the future to be resolved, or be notified asynchronously when it does through an event. In this latter case, the task is always responsive to new incoming messages.

Tasks can also be assigned loops to periodically execute at regular intervals, as well as started and stopped at runtime to save resources. Hooks can be registered in those instances to initialize or deinitialize resources if desired.

Tasks normally have an assigned isolated context which is not meant to accessible externally.

## How does it look like?

Here are some code snippets to give a general idea on how futures work in AsyncRTOS.

Here's how we define and declare an asynchronous function:
```c
AOS_DEFINE(some_async_func, int someParam)
AOS_DECLARE(some_async_func, int)
void some_async_func(aos_future_t *future) {
	AOS_ARGS_T(some_async_func) *args = aos_args_get(future);
	// Do something here, like printing
	printf("%d\n", args->someParam);
	// Mark future as resolved
	aos_resolve(future);
}
```

You can await the function synchronously with an awaitable:
```c
aos_future_t *future = AOS_AWAITABLE_ALLOC_T(some_async_func)(1);
aos_await(some_async_func(future));
aos_awaitable_free(future);
```

Or, in a task, be notified asynchronously when the function completes by using an eventful:

```c
aos_eventful_config_t config = {
    .task = source_task,
    .event = RESPONSE
};
aos_future_t *future = AOS_EVENTFUL_ALLOC_T(some_async_func)(&config, 1);
some_async_func(future);
```

For some real-life uses of these techniques and example projects, check the following section.

## Are there some examples I can start with?

Sure, first take a look at the example folder in this repository. Following the examples in order should give you an idea on how to best use AsyncRTOS features and structure your code.

Additionally, you can check out some ESP-IDF components made with it:

- [AsyncRTOS WiFi client](https://github.com/maikeriva/asyncrtos-wifi-client): An idempotent WiFi client. Shows how to convert an existing API into an idempotent AsyncRTOS task.
- [AsyncRTOS Websocket client](https://github.com/maikeriva/asyncrtos-websocket-client): A Websocket client reimplementation for ESP-IDF. Also shows how to implement idempotent tasks and asynchronous communication. 
- [AsyncRTOS JSON-RPC modules](https://github.com/maikeriva/asyncrtos-json-rpc): JSON-RPC client, server, and peer modules for ESP-IDF. Shows how AsyncRTOS can also be used to implement branched execution on a shared context.

In the JSON-RPC modules repository you can also find a meaningful example on how to achieve an asynchronous JSON-RPC server on an ESP32.

## Where can I read more?

I am working on improving the documentation in my free time, and I will be quicker if I see some interest in it :) Please show your support.

## How do I support this?

Contribute code, ask questions, or buy me a coffee :) 

<a href="https://www.buymeacoffee.com/micriv" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
