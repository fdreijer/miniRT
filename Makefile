NAME = miniRT
CC = cc -Wall -Werror -Wextra

LIBFT_PATH = inc/libft
LIBFT = ./inc/libft/libft.a

MLXPATH = inc/MLX42
MLX = inc/MLX42/build/libmlx42.a

LIBFT_INCL = -I inc/libft/inc
INCL = -I inc $(LIBFT_INCL) -I inc/MLX42/include/MLX42

BUILD_FOLDER = build

SRCS =	src/main.c	src/parsing.c	src/vector.c	src/free_exit.c	src/intersects.c	src/get_color.c \
src/rays.c

OBJS := $(patsubst src/%.c, $(BUILD_FOLDER)/%.o, $(SRCS))

all: libmlx libft $(NAME)

libmlx:
				@cmake -Wno-dev $(MLXPATH) -B $(MLXPATH)/build && make -C $(MLXPATH)/build -j4

$(NAME): $(OBJS) $(LIBFT) Makefile
				$(CC) $(OBJS) $(LIBFT) $(MLX) $(INCL) -lm -lglfw -o $(NAME)

$(BUILD_FOLDER)/%.o: src/%.c Makefile | $(BUILD_FOLDER)
				$(CC) $(INCL) -c -o $@ $<

$(BUILD_FOLDER):
				mkdir -p $@

libft:
				make -C $(LIBFT_PATH)

clean:
				make -C $(LIBFT_PATH) clean
				rm -rf $(BUILD_FOLDER)
				@rm -rf $(MLXPATH)/build

fclean: clean
				make -C $(LIBFT_PATH) fclean
				rm -f $(NAME)

re:				fclean all

.PHONY:			all clean fclean re libft