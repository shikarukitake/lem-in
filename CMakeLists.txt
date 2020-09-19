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
add_executable(lem_in ./general/srcs/main.c ./general/srcs/service.c ./general/srcs/bellman_ford.c ./general/srcs/dynamic_array.c ./general/srcs/edge.c ./general/srcs/solve.c ./general/srcs/t_node.c ./general/srcs/run_ants.c ./general/srcs/var.c ./general/srcs/count_steps.c ./general/srcs/set_in_way.c ./general/srcs/service_2.c ./general/srcs/solution.c ./general/srcs/copy_paths.c ./general/srcs/find_edge.c ./general/srcs/find_edge_functions.c ./general/srcs/get_edge.c ./general/srcs/delete_copies.c ./general/srcs/delete_disjoint.c ./general/srcs/dublicate_nodes.c ./general/srcs/edge_2.c ./general/srcs/make_paths.c ./general/srcs/reading_b.c ./general/srcs/reading_struct_helper.c ./general/srcs/reading_room.c ./general/srcs/reading_link.c ./general/srcs/reading_help_functions.c ./general/srcs/reading_check_after.c ./general/srcs/convert_structure.c ./general/srcs/flags.c ./general/srcs/print_nodes.c ./general/srcs/convert_structure2.c
 ./general/srcs/main.c ./general/srcs/service.c ./general/srcs/bellman_ford.c ./general/srcs/dynamic_array.c ./general/srcs/edge.c ./general/srcs/solve.c ./general/srcs/t_node.c ./general/srcs/run_ants.c ./general/srcs/var.c ./general/srcs/count_steps.c ./general/srcs/set_in_way.c ./general/srcs/service_2.c ./general/srcs/solution.c ./general/srcs/copy_paths.c ./general/srcs/find_edge.c ./general/srcs/find_edge_functions.c ./general/srcs/get_edge.c ./general/srcs/delete_copies.c ./general/srcs/delete_disjoint.c ./general/srcs/dublicate_nodes.c ./general/srcs/edge_2.c ./general/srcs/make_paths.c ./general/srcs/reading_b.c ./general/srcs/reading_struct_helper.c ./general/srcs/reading_room.c ./general/srcs/reading_link.c ./general/srcs/reading_help_functions.c ./general/srcs/reading_check_after.c ./general/srcs/convert_structure.c ./general/srcs/flags.c ./general/srcs/print_nodes.c ./general/srcs/convert_structure2.c)
target_link_libraries(lem_in ${PROJECT_BINARY_DIR}/libftprintf.a)
add_dependencies(lem_in ftprintf)

add_custom_target(my_test COMMAND make -C ${FdF_SOURCE_DIR}
        CLION_EXE_DIR=${PROJECT_BINARY_DIR})