# Memory-Allocator

RAM Memory
    Static byte array to represent the actual RAM space, that can be used.
    Linked list to represent the free memory holes in the RAM
    Becuase RAM is presented in bytes unit, so we can have the memory in terms of bytes

Empty Memory Holes:
    A linked List should be used
    It should contain the first index of the free memory block/hole and the size of this free block

Implement:
    void* my_malloc(size_t size)
    void my_free(void* ptr)
    void* my_calloc(size_t num, size_t size)
    void* my_realloc(void* ptr, size_t size)