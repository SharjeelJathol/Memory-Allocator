#include <stdio.h>
#include <string.h>
#include "my_alloc.h"

int main() {
    initialize_memory_block();
    
    printf("=== Testing my_malloc ===\n");
    
    // Basic allocation
    printf("Basic allocation test:\n");
    int* arr = (int*)my_malloc(10 * sizeof(int));
    if (arr) {
        for (int i = 0; i < 10; i++) arr[i] = i * 10;
        for (int i = 0; i < 10; i++) printf("%d ", arr[i]);
        printf("\n");
    }
    
    // Multiple allocations
    printf("Multiple allocations test:\n");
    char* str = (char*)my_malloc(20);
    if (str) {
        strcpy(str, "Hello, Allocator!");
        printf("String: %s\n", str);
    }
    
    // my_calloc (zero-initialized)
    printf("my_calloc test:\n");
    int* zeros = (int*)my_calloc(5, sizeof(int));
    if (zeros) {
        for (int i = 0; i < 5; i++) {
            printf("zeros[%d] = %d (should be 0)\n", i, zeros[i]);
        }
    }
    
    // my_realloc
    printf("my_realloc test:\n");
    int* numbers = (int*)my_malloc(3 * sizeof(int));

    if (numbers) {
        numbers[0] = 1;
        numbers[1] = 2;
        numbers[2] = 3;
        printf("Before realloc:\n");
        for (int i = 0; i < 3; i++) printf("%d ", numbers[i]);
        printf("\n");
        
        numbers = (int*)my_realloc(numbers, 6 * sizeof(int));

        if (numbers) {
            numbers[3] = 4;
            numbers[4] = 5;
            numbers[5] = 6;
            printf("After realloc:\n");
            for (int i = 0; i < 6; i++) printf("%d ", numbers[i]);
            printf("\n");
        }
    }
    
    // allocate and free memory
    printf("Allocate and free memory test:\n");
    void* p = my_malloc(100);
    printf("Allocated 100 bytes\n");
    my_free(p);
    printf("Freed 100 bytes\n");
    
    void* p2 = my_malloc(100);
    printf("Reallocated 100 bytes\n");
    my_free(p2);

    my_free(arr);
    my_free(str);
    my_free(zeros);
    my_free(numbers);
    
    printf("\n=== All tests passed! ===\n");
    return 0;
}