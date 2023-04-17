# AsyncRTOS

AsyncRTOS is a framework for developing asynchronous and multithreaded applications on top of ESP-IDF and other FreeRTOS SMP variants. It is written in C and abstracts away the complexity of working on multi-core SoCs such as ESP32.

In a nutshell, AsyncRTOS allows to create isolated tasks which can float independently on any available core, and communicate safely between them through futures. Like in other programming languages (C#, C++, Java) futures represent the state of an operation, and can be awaited synchronously for their completion or made to asynchronously invoke a callback.

This allows to build firmwares as ecosystems of microservices with deterministic behavior. When designed right, these services are idempotent and allow for a declarative programming approach.

To get started take a look at the examples in the repository, or check out some of the demo projects:

- AOS WiFi client (soon)
- AOS Websocket client (soon)
- AOS JSON-RPC server, client, and peer (soon)
- Example implementation of a JSON-RPC peer over Websocket on ESP32. (soon)
