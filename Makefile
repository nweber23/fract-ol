NAME = fractol
SRC = srcs/main.c
OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS = -O3 -Wall -Wextra -Werror -I./includes/

# OS detection
UNAME_S := $(shell uname -s)

# MLX42 configuration
MLX_DIR = ./MLX42
MLX_BUILD_DIR = $(MLX_DIR)/build
MLX_LIB = $(MLX_BUILD_DIR)/libmlx.a
MLX_INC = -I$(MLX_BUILD_DIR)
MLX_REPO = https://github.com/codam-coding-college/MLX42.git

# Platform-specific settings
ifeq ($(UNAME_S),Linux)
	# Linux configuration
	MLX_FLAGS = -L$(MLX_BUILD_DIR) -lmlx42 -ldl -lglfw -lm -pthread
	CFLAGS += -D LINUX
else ifeq ($(UNAME_S),Darwin)
	# macOS configuration
	MLX_FLAGS = -L$(MLX_BUILD_DIR) -lmlx42 -lglfw -framework Cocoa -framework OpenGL -framework IOKit
	CFLAGS += -D OSX
else
	$(error OS not supported: $(UNAME_S))
endif

all: $(NAME)

$(NAME): $(OBJ) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(MLX_FLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(MLX_INC) -c $< -o $@

$(MLX_LIB): | $(MLX_DIR)
	cd $(MLX_DIR) && cmake -B build && cmake --build build -j4

$(MLX_DIR):
	@if [ ! -d "$(MLX_DIR)/.git" ]; then \
		echo "Cloning MLX42 repository..."; \
		git clone $(MLX_REPO) $(MLX_DIR); \
	else \
		echo "MLX42 repository already exists. Skipping clone."; \
	fi

clean:
	rm -f $(OBJ)
	if [ -d "$(MLX_BUILD_DIR)" ]; then $(MAKE) clean -C $(MLX_BUILD_DIR); fi

fclean: clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re