cmake_minimum_required(VERSION 3.16)
project(lem_in_42 C)

set(CMAKE_C_STANDARD 11)

include_directories(general/includes)
include_directories(general/libftprintf/includes)
include_directories(minilibx/)

# Libft
file(GLOB_RECURSE LIBFT_FILES "${PROJECT_SOURCE_DIR}/general/libftprintf/srcs/*.c")
set(LIBFT_FILES ${LIBFT_FILES} ${LIBFT_ADD_FILES})
add_library(ftprintf STATIC ${LIBFT_FILES})


# lem-in
add_executable(lem_in general/srcs/main.c general/includes/lem_in.h general/srcs/reading.c general/srcs/service.c general/srcs/solve.c general/srcs/dynamic_array.c general/srcs/t_node.c general/srcs/bellman_ford.c general/srcs/edge.c general/srcs/suurbale.c)
target_link_libraries(lem_in ${PROJECT_BINARY_DIR}/libftprintf.a)
add_dependencies(lem_in ftprintf)

add_custom_target(my_test COMMAND make -C ${FdF_SOURCE_DIR}
        CLION_EXE_DIR=${PROJECT_BINARY_DIR})