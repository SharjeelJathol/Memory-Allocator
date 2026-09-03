#include "stdio.h"
#include "my_alloc.h"
#include "string.h"

#define RAM_size (1024 * 1024)   // 1MB RAM size
static unsigned char memory_size[RAM_size];

typedef struct Memory_Block {
    size_t block_size;
    struct Memory_Block* next;
} Memory_Block;

static Memory_Block* free_blocks = NULL;

void initialize_memory_block(){
    free_blocks = (Memory_Block*)memory_size;
    free_blocks->block_size = RAM_size - sizeof(Memory_Block);  // Header space
    free_blocks->next = NULL;
}

void* my_malloc(size_t required_memory_size){

    if(required_memory_size == 0){
        return NULL;
    }

    if(free_blocks == NULL){
        initialize_memory_block();
    }

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
              
            } else {
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
        }

        prev = current;
        current = current->next;
    }

    return NULL;
}

void my_free(void* ptr_to_memory_space_to_be_freed){
    if(ptr_to_memory_space_to_be_freed == NULL){
        return;
    }

    struct Memory_Block* block_to_be_freed = (struct Memory_Block*)((char*)ptr_to_memory_space_to_be_freed - sizeof(Memory_Block));
    block_to_be_freed->next = free_blocks;
    free_blocks = block_to_be_freed;
    block_to_be_freed = NULL;
    return;
}

void* my_realloc(void* ptr_to_memory_space, size_t new_size){
    if(ptr_to_memory_space == NULL){
        return NULL;
    }

    void* new_ptr = my_malloc(new_size);
    if(new_ptr == NULL) return NULL;

    // create new block with updated size
    struct Memory_Block* new_block = (struct Memory_Block*)((char*)new_ptr - sizeof(Memory_Block));
    if(new_block == NULL){
        return NULL;
    }

    // get reference to the old block
    struct Memory_Block* current_block = (struct Memory_Block*)((char*)ptr_to_memory_space - sizeof(Memory_Block));
    size_t current_size = current_block->block_size;

    // copy the elements to the new block
    memcpy((char*)new_block + sizeof(Memory_Block), ptr_to_memory_space, current_size < new_size ? current_size : new_size);

    // Put the current block back into the free list
    current_block->next = free_blocks;
    free_blocks = current_block;
    current_block = NULL;

    // return the writable address of the new block i.e. excluding the header
    return (char*)new_block + sizeof(Memory_Block);

}

void* my_calloc(size_t number_of_elements, size_t size_of_element){
    size_t total_size = number_of_elements * size_of_element;

    void* ptr = my_malloc(total_size);
    if(ptr){
        for(size_t i = 0; i < total_size; i++){
            ((unsigned char*)ptr)[i] = 0;
        }
    }

    return ptr;
}
