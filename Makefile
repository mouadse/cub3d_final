# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/10 12:31:32 by msennane          #+#    #+#              #
#    Updated: 2025/06/05 13:47:55 by msennane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -O3 #-g3 -fsanitize=leak,address,undefined
MLXFLAGS = -lmlx -lXext -lX11 -lm

# Directories
LIBFT_DIR = libft
GNL_DIR = get_next_line

# Source files
SRCS = main.c validation.c check_path.c data_processing.c \
	check_rgb.c map.c map_utils.c tabs.c utils.c check_wall.c \
	camera.c event_hooks.c raycasting.c raycasting_utils.c \
	render_background.c textures.c vector_ops.c wall_rendering.c \
	wall_utils.c player_movement.c my_mlx_utils.c check_path_colors.c \
	check_path_identifiers.c check_path_textures.c map_utils2.c \
	utils2.c vector_ops2.c check_rgb2.c

# Get_next_line files
GNL_SRCS = $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c

# Object files
OBJS = $(SRCS:.c=.o)
GNL_OBJS = $(GNL_SRCS:.c=.o)

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a

# Rules
all: $(NAME)

$(NAME): $(OBJS) $(GNL_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(GNL_OBJS) $(LIBFT) $(MLXFLAGS) -o $(NAME)
	@echo "\033[32mCompilation successful! '$(NAME)' is ready.\033[0m"

$(LIBFT):
	@echo "\033[33mCompiling Libft...\033[0m"
	@make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -I. -I$(LIBFT_DIR) -I$(GNL_DIR) -c $< -o $@

clean:
	@echo "\033[33mCleaning object files...\033[0m"
	@rm -f $(OBJS) $(GNL_OBJS)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@echo "\033[33mCleaning executable...\033[0m"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

test:
	@echo "Running basic execution tests with sanitizers..."
	@echo "Please close the game window manually if it opens, to proceed to the next test."
	@echo "Observe the console for sanitizer messages or crashes."
	@sh ./run_tests.sh

.PHONY: all clean fclean re test
.SECONDARY: $(OBJS)
