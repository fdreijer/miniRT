NAME = miniRT
CC = cc -Wall -Werror -Wextra

LIBFT_PATH = libft
LIBFT = ./libft/libft.a

LIBFT_INCL = -I libft/inc
INCL = -I inc $(LIBFT_INCL) -I./libft/inc

BUILD_FOLDER = build

SRCS =	src/main.c

OBJS := $(patsubst src/%.c, $(BUILD_FOLDER)/%.o, $(SRCS))

all: libft $(NAME)

$(NAME): $(OBJS) $(LIBFT) Makefile
	$(CC) $(OBJS) $(LIBFT) $(INCL) -lm -o $(NAME)

$(BUILD_FOLDER)/%.o: src/%.c Makefile | $(BUILD_FOLDER)
	$(CC) $(INCL) -c -o $@ $<

$(BUILD_FOLDER):
	mkdir -p $@

libft:
	make -C $(LIBFT_PATH)

clean:
	make -C $(LIBFT_PATH) clean
	rm -rf $(BUILD_FOLDER)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft