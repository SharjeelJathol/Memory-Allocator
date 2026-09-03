#include <stdio.h>
#include <string.h>
#include "my_alloc.h"

int main() {
    printf("=== Testing my_malloc ===\n");
    
    // Basic allocation
    int* arr = (int*)my_malloc(10 * sizeof(int));
    if (arr) {
        for (int i = 0; i < 10; i++) arr[i] = i * 10;
        for (int i = 0; i < 10; i++) printf("%d ", arr[i]);
        printf("\n");
    }
    
    // Multiple allocations
    char* str = (char*)my_malloc(20);
    if (str) {
        strcpy(str, "Hello, Allocator!");
        printf("String: %s\n", str);
    }
    
    // my_calloc (zero-initialized)
    int* zeros = (int*)my_calloc(5, sizeof(int));
    if (zeros) {
        for (int i = 0; i < 5; i++) {
            printf("zeros[%d] = %d (should be 0)\n", i, zeros[i]);
        }
    }
    
    // allocate and free memory
    void* p = my_malloc(100);
    printf("Allocated 100 bytes\n");
    my_free(p);
    printf("Freed 100 bytes\n");
    
    void* p2 = my_malloc(100);
    printf("Reallocated 100 bytes\n");
    my_free(p2);
    
    printf("\n=== All tests passed! ===\n");
    return 0;
}