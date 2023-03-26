// https://github.com/ThrowTheSwitch/Unity/blob/master/docs/UnityAssertionsReference.md
#include <esp_heap_trace.h>

#define TEST_HEAP_START                                      \
    {                                                        \
        printf("Heap tracing started\n");                    \
        ESP_ERROR_CHECK(heap_trace_start(HEAP_TRACE_LEAKS)); \
    }

#define TEST_HEAP_STOP                      \
    {                                       \
        ESP_ERROR_CHECK(heap_trace_stop()); \
        heap_trace_dump();                  \
        printf("Heap tracing ended\n");     \
    }

#define TEST_HEAP(instructions)                      \
    {                                                \
        TEST_HEAP_START{instructions} TEST_HEAP_STOP \
    }
