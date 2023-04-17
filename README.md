# AsyncRTOS

AsyncRTOS is a framework for developing asynchronous and multithreaded applications on top FreeRTOS SMP variants such as ESP-IDF. It is written in C and works on SoCs with an arbitrary number of cores.

In a nutshell, AsyncRTOS provides an asynchronous IPC mechanism for tasks which uses futures. Similarly to other languages, futures represent the state of a current operation whose result can be awaited synchronously or callback asynchronously.

This allows to build firmwares as ecosystems of microservices which are isolated, idempotent, and communicate between them in a thread-safe and deterministic manner on multi-core SoCs such as ESP32.

To get started take a look at the examples in the repository, or check out some of the demo projects:

- AOS WiFi client
- AOS Websocket client
- AOS JSON-RPC utils (server, client, peer)
- Example implementation of a JSON-RPC peer over Websocket on ESP32.
