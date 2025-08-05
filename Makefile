NAME = cub3d

SRCS = srcs/main.c \
		srcs/raycasting/init.c \
		srcs/raycasting/rendering.c \
		srcs/raycasting/hooks_utils.c \
		srcs/raycasting/raycasting.c

LIBFT_DIR = ./libraries/libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = ./libraries/minilibx-linux
MLX_LIB = ./libraries/minilibx-linux/libmlx.a

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
MLX_FLAGS = -lmlx -lXext -lX11 -lm -lz
RM = rm -f

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(MLX_FLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX_LIB)

$(LIBFT):
	make bonus -C $(LIBFT_DIR)

all: $(NAME)

run: all
	./cub3d

clean:
	$(RM) $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: ${OBJS}