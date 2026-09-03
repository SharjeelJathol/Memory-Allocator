#ifndef MA_ALLLOC_H
#define MA_ALLLOC_H

void* my_malloc(size_t required_memory_size);
void my_free(void* ptr_to_memory_space_to_be_freed);
void* my_calloc(size_t number_of_elements, size_t size_of_element);
void* my_realloc(void* ptr_to_memory_space, size_t new_size);

#endif