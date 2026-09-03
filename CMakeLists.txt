cmake_minimum_required(VERSION 3.10)
project(MemoryAllocator)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)

add_executable(test_allocator_c 
    my_alloc.c
    main.c
)

add_custom_target(valgrind_c
    COMMAND valgrind --leak-check=full --show-leak-kinds=all ./test_allocator_c
    DEPENDS test_allocator_c
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
