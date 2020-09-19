NAME_1 = lem-in

LIBFT_A = libftprintf.a

SR_LI_1 =	main.c \
			service.c \
			bellman_ford.c \
			dynamic_array.c \
			edge.c \
			solve.c \
			t_node.c \
			run_ants.c \
			var.c \
			count_steps.c \
			set_in_way.c \
			service_2.c \
			solution.c \
			copy_paths.c \
			find_edge.c \
			find_edge_functions.c \
			get_edge.c \
			delete_copies.c \
			delete_disjoint.c \
			dublicate_nodes.c \
			edge_2.c \
			make_paths.c \
			reading_b.c \
			reading_struct_helper.c \
			reading_room.c \
			reading_link.c \
			reading_help_functions.c \
			reading_check_after.c \
			convert_structure.c \
			flags.c \
			print_nodes.c \
			convert_structure2.c \

SOURCES_DIR = ./general/srcs/

SRCS_LI_1 = $(addprefix $(SOURCES_DIR), $(SR_LI_1))
OBJECT_DIR_1 = objects1/
OBJ_LIST_LI_1 = $(patsubst %.c, %.o, $(SR_LI_1))
OBJ_LI_1 = $(addprefix $(OBJECT_DIR_1), $(OBJ_LIST_LI_1))

HEADER_DIR = ./general/includes/

LIB_MLX = minilibx/libmlx.a
LIBS_MLX = -L./ft_printf -lftprintf
MLX_DIR = ./minilibx

COMPILER := gcc
HDRPATH := ./general/includes -I./general/libftprintf/includes -I./minilibx
IFLAGS := -I$(HDRPATH)
CFLAGS := -Wall -Wextra -Werror -O2

LIB_DIR = ./general/libftprintf
LIB_RULE = $(addsuffix .lib, $(LIB_DIR))

LIBFT = ./general/libftprintf/libftprintf.a
LIBS = -L./general/ft_libftprintf -l_ftprintf


all: $(LIB_RULE) $(NAME_1)

%.lib:
	@$(MAKE) -sC $(LIB_DIR)

$(NAME_1): $(LIBFT) $(OBJECT_DIR_1) $(OBJ_LI_1)
	@$(COMPILER) $(CFLAGS) $(IFLAGS) $(LIBFT) $(OBJ_LI_1) -o $(NAME_1)
	@echo "\x1b[32mlem-in compiled\x1b[0m"
$(OBJECT_DIR_1):
	@mkdir -p $(OBJECT_DIR_1)

$(OBJECT_DIR_1)%.o : $(SOURCES_DIR)%.c $(HEADERS)
	@$(COMPILER) $(CFLAGS) -c $(IFLAGS) $< -o $@

$(LIBFT):
	@make -C $(LIB_DIR)

clean:
	@rm -rf $(OBJECT_DIR_1)
	@make -C $(LIB_DIR) clean
	@rm -rf $(OBJECT_PF)

fclean: clean
	@make -C $(LIB_DIR) fclean
	@/bin/rm -f $(NAME_1)

re: fclean all
