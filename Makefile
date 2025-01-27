.PHONY: all clean fclean re recomp

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR) -I./mlx_linux

NAME = so_long

SRCS = main.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX = mlx/libmlx.a


$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(MLX) $(OBJS) Makefile
	$(CC) $(OBJS) -L$(LIBFT_DIR) -lft -L./mlx -lmlx -lXext -lX11 -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
