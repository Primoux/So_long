.PHONY: all clean fclean re print-

CC		= cc
CFLAGS	= -I $(INCLUDE_DIR) -I ./src/lib/libft/include -Wall -Wextra
NAME	= so_long

LIBFT_DIR	= src/lib/libft
INCLUDE_DIR = src/include
MLX_DIR		= src/lib/mlx/libmlx.a
PARSING_DIR = src/parsing/
OBJ_DIR		= obj/

PARSING_SRCS	=  parsing.c
LIBFT			= $(LIBFT_DIR)/libft.a


SRCS =	$(addprefix $(PARSING_DIR), $(PARSING_SRCS))

OBJS = $(patsubst %.c,$(OBJ_DIR)%.o,$(SRCS))
DEPENDENCIES = $(OBJS:.o=.d)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS)  -o $(NAME) $(LIBFT)

-include $(DEPENDENCIES)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@ 


clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

print-%:
	@echo $($(patsubst print-%,%,$@))