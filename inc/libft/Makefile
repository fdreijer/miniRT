NAME = libft.a
CC = cc
CFLAGS = -Wall -Werror -Wextra -I inc
SRCS =  src/ft_atoi.c		src/ft_calloc.c			src/ft_isspace.c \
		src/ft_itoa.c		src/ft_memmove.c		src/ft_realloc.c \
		src/ft_split.c 		src/ft_strcmp.c			src/ft_strjoin.c \
		src/ft_strlen.c		src/ft_strncmp.c		src/ft_strndup.c \
		src/ft_min.c		src/ft_strchr.c			src/get_next_line.c \
		src/split_space.c	src/ft_atof.c			src/ft_isdigit.c

INCLS = inc/libft.h

BUILD_FOLDER = build
OBJS := $(patsubst src/%.c, $(BUILD_FOLDER)/%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS) Makefile $(INCLS)
	ar rcsUu $(NAME) $(OBJS)

$(BUILD_FOLDER)/%.o: src/%.c Makefile $(INCLS) | $(BUILD_FOLDER)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_FOLDER):
	mkdir -p $@

clean:
	rm -rf $(BUILD_FOLDER)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re