#include "stdio.h"
#include "my_alloc.h"

#define RAM_size (1024 * 1024)   // 1MB RAM size
static unsigned char memory_size[RAM_size];

typedef struct Memory_Block {
    size_t block_size;
    struct Memory_Block* next;
} Memory_Block;

struct test {
    int integer;
};

static Memory_Block* free_blocks = NULL;

void initialize_memory_block(){
    free_blocks = (Memory_Block*)memory_size;
    free_blocks->block_size = RAM_size - sizeof(Memory_Block);  // Header space
    free_blocks->next = NULL;
}

void* my_malloc(size_t required_memory_size){
    struct Memory_Block* current = free_blocks;
    struct Memory_Block* prev = NULL;

    while(current){
        
        if(current->block_size >= required_memory_size){
            // Block size is greater than or equal tothe required size.

            if(current->block_size > (required_memory_size + sizeof(Memory_Block))){
                // Block size should at least be greather than the size required and
                //  the header for the new block
                // Break the block into 2. 
                // Create a new free memory block
                struct Memory_Block* new_block = (Memory_Block*)((char*)current + sizeof(Memory_Block) + required_memory_size);
                new_block->block_size = current->block_size - required_memory_size - sizeof(Memory_Block);
                new_block->next = current->next;

                current->block_size = required_memory_size;
                current->next = NULL;

                if(prev){
                    prev->next = new_block;
                }else{
                    free_blocks = new_block;
                }
                new_block = NULL;
                prev = NULL;
                return (char*)current + sizeof(Memory_Block);
              
            }
            else{
                // Exactly equal to the required size
                // Perfect sized block found
                if(prev){
                    prev->next = current->next;
                }else{
                    free_blocks = current->next;
                    current->next = NULL;
                }
                prev = NULL;
                return (char*)current + sizeof(Memory_Block);
            }

            prev = current;
            current = current->next;
        }

        return NULL;
    }
}

int main(){
    initialize_memory_block();
    printf("Size of Memory Block: %ld\n", sizeof(Memory_Block));
    printf("free_blocks:     %p\n", free_blocks);
    char* array = (char*)my_malloc(10);
    printf("array:           %p\n", array);
    printf("free_blocks:     %p\n", free_blocks);
    char* array2 = (char*)my_malloc(16);
    printf("array2:          %p\n", array2);
    printf("free_blocks:     %p\n", free_blocks);

    // printf("%ld\n", free_blocks->block_size);
    return 0;
}