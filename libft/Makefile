# Project Configuration
NAME = libft.a

# Directory structure
PRINTF_DIR = printf/srcs
OBJ_DIR = objs

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
	ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
	ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
	ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
	ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
	ft_atoi.c ft_calloc.c ft_substr.c ft_strjoin.c \
	ft_strdup.c ft_strtrim.c ft_split.c ft_itoa.c \
	ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
	ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_sqrt.c \
	ft_atof.c ft_strcmp.c

BONUS_SRCS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
		ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

PRINTF_SRCS = ft_printf.c putstr.c putnbr.c

# Object files
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
BONUS_OBJS = $(addprefix $(OBJ_DIR)/, $(BONUS_SRCS:.c=.o))
PRINTF_OBJS = $(addprefix $(OBJ_DIR)/, $(PRINTF_SRCS:.c=.o))

# Compiler configuration
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -I$(PRINTF_DIR)
RM = rm -f

# Build rules
all: $(NAME)

$(NAME): $(OBJS) $(PRINTF_OBJS)
	ar rcs $(NAME) $(OBJS) $(PRINTF_OBJS)

bonus: $(OBJS) $(BONUS_OBJS) $(PRINTF_OBJS)
	ar rcs $(NAME) $(OBJS) $(BONUS_OBJS) $(PRINTF_OBJS)

# Rule for libft sources (in root directory)
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule for printf sources (in printf folder)
$(OBJ_DIR)/%.o: $(PRINTF_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re bonus