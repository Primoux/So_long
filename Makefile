#-------------------------------- VARIABLES --------------------------------#

NAME		=	so_long
CC		 	=	cc
CFLAGS		=	-Wall -Wextra -Werror
SHELL 		=	/bin/bash

#-------------------------------- DEFINE ----------------------------------#

WIDTH   =	$(shell xrandr | grep current | awk '{print $$8}')
HEIGHT  =	$(shell xrandr | grep current | awk '{print $$10}' | sed --expression s/,/''/)
DEFINE  =	-D WIDTH=$(WIDTH) -D HEIGHT=$(HEIGHT)

#-------------------------------- DIRECTORIES --------------------------------#

LIBFT_DIR		=	src/lib/libft
LIBMLX_DIR		=	src/lib/mlx
INCLUDE_DIR		=	src/include
PARSING_DIR		=	src/parsing/
INIT_DIR		=	src/init/
HANDLE_MLX_DIR	=	src/handle_mlx/
UTILS_DIR		=	src/utils/
OBJ_DIR			=	obj/

#-------------------------------- INCLUDES & FLAGS --------------------------------#

INCLUDES	=	-I $(INCLUDE_DIR) \
				-I ./src/lib/libft/include \
				-I $(LIBMLX_DIR)

LDFLAGS		=	-L$(LIBMLX_DIR) -lmlx \
				-lXext -lX11 -lm

#-------------------------------- LIBRARIES --------------------------------#

LIBFT		= $(LIBFT_DIR)/libft.a
MLX			= $(LIBMLX_DIR)/libmlx.a

#-------------------------------- SOURCE FILES --------------------------------#

PARSING_SRCS	=	parsing.c check_map.c check_char.c \
					find_e_and_p.c flood_fill.c check_argv.c

INIT_SRCS		=	init_game.c init_window.c

HANDLE_MLX_SRCS	=	mlx_destroy.c mlx_utils.c movement.c mlx_print_utils.c

UTILS_SRCS		=	aff_map.c

SRCS			=	$(addprefix $(PARSING_DIR), $(PARSING_SRCS)) \
					$(addprefix $(INIT_DIR), $(INIT_SRCS)) \
					$(addprefix $(HANDLE_MLX_DIR), $(HANDLE_MLX_SRCS)) \
					$(addprefix $(UTILS_DIR), $(UTILS_SRCS))

#-------------------------------- OBJECTS --------------------------------------#

OBJS			=	$(patsubst %.c,$(OBJ_DIR)%.o,$(SRCS))
DEPENDENCIES	=	$(OBJS:.o=.d)

#-------------------------------- PROGRESS BAR --------------------------------#

TOTAL_FILES		:=	$(shell find $(SRCS) -type f -name "*.c" -newer $(NAME) 2>/dev/null | wc -l)
ifeq ($(TOTAL_FILES),0)
	TOTAL_FILES =	$(words $(SRCS))
endif
CURRENT_FILE	:=	0
BAR_LENGTH		:=	50

#-------------------------------- COLORS --------------------------------#

# Define colors and style
BLACK		:=	\033[38;2;0;0;0m
RED			:=	\033[38;2;220;20;60m
GREEN		:=	\033[38;2;46;139;87m
BLUE		:=	\033[38;2;30;144;255m
YELLOW		:=	\033[38;2;255;215;0m
MAGENTA		:=	\033[38;2;186;85;211m
CYAN		:=	\033[38;2;0;206;209m
WHITE		:=	\033[38;2;255;255;255m
ORANGE		:=	\033[38;2;255;140;0m
PURPLE		:=	\033[38;2;147;112;219m
RESET		:=	\033[0m
BOLD		:=	\033[1m

# Simplified progress bar function
define draw_progress_bar
	@printf "\r$(CYAN)$(BOLD)Compiling so_long: $(RESET)["
	@n=$(CURRENT_FILE); \
	total=$(TOTAL_FILES); \
	pct=`expr $$n '*' 100 / $$total`; \
	fill=`expr $$n '*' $(BAR_LENGTH) / $$total`; \
	empty=`expr $(BAR_LENGTH) - $$fill`; \
	printf "$(GREEN)%*s$(RESET)" $$fill "" | tr ' ' '='; \
	printf "%*s" $$empty "" | tr ' ' ' '; \
	printf "] $(BOLD)%3d%%$(RESET) (%d/%d)" $$pct $$n $$total; \
	if [ $$n = $$total ]; then printf "\n"; fi
endef

#-------------------------------- RULES --------------------------------#


all: $(NAME)

$(LIBFT): libft

$(MLX): mlx

mlx :
	@$(MAKE) --silent -C $(LIBMLX_DIR) 

libft:
	@$(MAKE) --silent -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@printf "$(BLUE)$(BOLD)Linking objects...$(RESET)\n"
	@$(CC) $(OBJS) -o $(NAME)  $(LIBFT) $(LDFLAGS)
	@printf "$(GREEN)$(BOLD)Build successful!$(RESET) Created $(BOLD)$(NAME)$(RESET)\n"


# Update compilation rule
$(OBJ_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
	$(call draw_progress_bar)
	@$(CC) $(CFLAGS) $(DEFINE) $(INCLUDES) -MMD -MP -c $< -o $@
	@if [ $(CURRENT_FILE) = $(TOTAL_FILES) ]; then echo; fi

clean:
	@printf "$(BLUE)Cleaning object files from so_long...$(RESET)\n"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) --silent -C $(LIBFT_DIR) clean

fclean:
	@printf "$(BLUE)Removing library mlx...$(RESET)\n"
	@$(MAKE) --silent -C $(LIBMLX_DIR) clean
	@printf "$(GREEN)Clean complete mlx!$(RESET)\n"
	@$(MAKE) --silent -C $(LIBFT_DIR) fclean
	@printf "$(BLUE)Removing executable from so_long...$(RESET)\n"
	@rm -f $(NAME)
	@printf "$(BLUE)Cleaning object files from so_long...$(RESET)\n"
	@rm -rf $(OBJ_DIR)
	@printf "$(GREEN)Clean complete so_long!$(RESET)\n"


re: fclean
	@$(MAKE) --silent all

print-%:
	@echo $($(patsubst print-%,%,$@))

-include $(DEPENDENCIES)

.PHONY: all clean fclean re libft print-%