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
        Allocates a contiguous block of memory on the heap at runtime. The allocated memory is
         uninitialized, so its contents have an indeterminate value.
    void my_free(void* ptr)
        Frees allocated memory
    void* my_calloc(size_t num, size_t size)
        Allocates memory for multiple elements and initializes all allocated bytes to zero.
    void* my_realloc(void* ptr, size_t size)
        Changes the size of a previously allocated memory block. It can be used to increase or
         decrease the amount of dynamically allocated memory.

Allignment:
    Alligning for data types
    Memory address must be a multiple of its variable's size

Compiling:
    mkdir build
    cd build
    cmake ..
    make

Execution:
    ./test_allocator_c for execution
    make valgrind_c
    cmake --build . --target valgrind_c
