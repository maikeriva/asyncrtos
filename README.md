# AsyncRTOS

AsyncRTOS is a framework for developing asynchronous and multithreaded applications on top of multicore FreeRTOS SMP variants such as ESP-IDF.

With AsyncRTOS it becomes easier to implement an idempotent and thread-safe microservice architecture on FreeRTOS SMP variants such as ESP-IDF, thus favoring a declarative programming approach.

AsyncRTOS is an overlay on top of FreeRTOS and provides:
- Thread-safe IPC between tasks using a request-response pattern.
- Asynchronous functions

## Why?

There is no built-in way within ESP-IDF to safely communicate between tasks in a thread-safe and idempotent manner.

1. SMP opens the door to concurrency issues and race conditions. Particular care is required when developing applications consisting of multiple tasks.
2. Idempotent behavior is spotty within ESP-IDF, making declarative programming difficult.

Using AsyncRTOS allows to:

- Implement an idempotent and thread-safe microservice architecture.
- Parallelize processes on all available cores
- Have an IPC pattern
- 

When used alongside a specific set of design patterns, asyncsmp can greatly simplify the development of thread-safe and responsive applications while making full use of all available cores.

Some of the advantages provided include:

    Asynchronous programming through async/await and request/response style directives (similar to C#, Node, etc.)

    Thread safe by default (if design patterns are followed)

    Easy parallelization of processes

    Tasks are automatically run on any core available, minimizing idle time

    Light memory footprint (7 bytes of RAM average overhead per async operation)

    Tiny codebase (<1000 lines of code)

    Reduces necessity of establishing clear task priorities

    Unintrusive, can be used as necessary in specific components

## How?

You can find a few documented examples in the `example` directory.

### Example 1

Awaitables

- Create a new task
- Register a handler (delayed one, to simulate work)
- Alloc an awaitable future
- Send a request to that task
- Await for response
- Print "done"
- Cleanup

### Example 2

Callbackers

- Create a new task
- Register a handler (delayed one, to simulate work)
- Alloc a callbacker future
- Send a request to that task
- Print "done"
- Callback gets called
- Cleanup

Show that callbacker futures can be sent multiple times, the task won't block

### Example 3

IPC, forwarding

- Create task 0
- Register a sendrequest handler
- Register a processresponse handler
- Create task 1
- Register a handler (delayed one, to simulate work)
- Alloc a callbacker future
- Send a request to task 0
- Await for response
- Cleanup

Show that callbacker futures can be sent multiple times, the task won't block

Note that task 1 has no knowledge about the future sent by the main task, nor does it need to know. Processing futures is completely agnostic of both their type (awaitables, callbackers, forgettables, ipc) and their parents.

### Example 4

Forgettables

Spawning


## I like this, how can I contribute?

Feel free to contribute the usual Github way with issues, pull requests, forks, etc.

Or you can buy me a coffe [BUY ME A COFFEE SIGN].

# TODO:

- Consider introducing .handlers and .handlers_count fields to aos_task_config_t, so that handlers can be set through a declarative approach.


# Layout notes

- Dependencies which include aos_macros.h will also need access to _aos_macros.h. For this reason, we can't hide _aos_macros.h in PRIV_INCLUDE folders.