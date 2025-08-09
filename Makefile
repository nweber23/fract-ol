NAME = fractol
SRC = srcs/main.c srcs/phoenix.c srcs/mandelbrot.c srcs/render.c \
	srcs/zoom.c srcs/keyboard_utils.c srcs/julia.c \
	srcs/parsing.c srcs/colors.c
OBJ_DIR = objs
OBJ = $(SRC:srcs/%.c=$(OBJ_DIR)/%.o)
CC = cc
CFLAGS = -O3 -funroll-loops -flto -ftree-vectorize \
	-fomit-frame-pointer -finline-functions \
	-Wall -Wextra -Werror -I./includes/ -I./libft/includes/ \
	-pthread

# OS detection
UNAME_S := $(shell uname -s)

# Library paths
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

# MLX42 configuration
MLX42_DIR = ./MLX42

# Platform-specific settings
ifeq ($(UNAME_S),Linux)
	# Linux configuration
	LIBMLX42 = $(MLX42_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm
	CFLAGS += -D LINUX
else ifeq ($(UNAME_S),Darwin)
	# macOS configuration
	LIBMLX42 = $(MLX42_DIR)/build/libmlx42.a -lglfw -framework Cocoa -framework OpenGL -framework IOKit
	CFLAGS += -D OSX
else
	$(error OS not supported: $(UNAME_S))
endif

CFLAGS += -I$(MLX42_DIR)/include/MLX42

all: $(LIBFT) $(LIBMLX42) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBMLX42) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: srcs/%.c includes/fractol.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(LIBMLX42):
	@if [ ! -d $(MLX42_DIR) ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git \
		$(MLX42_DIR); \
	fi
	@if [ ! -f $(MLX42_DIR)/build/libmlx42.a ]; then \
		cmake $(MLX42_DIR) -B $(MLX42_DIR)/build && \
		cmake --build $(MLX42_DIR)/build -j4; \
	fi

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)
	@rm -rf $(MLX42_DIR)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re