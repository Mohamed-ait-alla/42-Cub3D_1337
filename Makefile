NAME = cub3d
NAMEB = cub3d_bonus

SRCS = srcs/mandatory/main.c \
		srcs/mandatory/raycasting/init.c \
		srcs/mandatory/raycasting/player_move.c \
		srcs/mandatory/raycasting/raycasting_utils.c \
		srcs/mandatory/raycasting/raycasting.c \
		srcs/mandatory/raycasting/rendering.c \
		srcs/mandatory/raycasting/rendering_utils.c \
		srcs/mandatory/raycasting/normalize.c \
		srcs/mandatory/raycasting/wall_collision.c \
		srcs/mandatory/raycasting/cleanup.c \
		srcs/mandatory/raycasting/launch.c \
		\
		srcs/mandatory/parsing/check_file_name.c \
		srcs/mandatory/parsing/helper-functions/custom_error.c \
		srcs/mandatory/parsing/check_map.c \
		libraries/get_next_line/get_next_line.c \
		srcs/mandatory/parsing/check_color.c \
		srcs/mandatory/parsing/check_num_of_players.c \
		srcs/mandatory/parsing/map_is_valid.c \
		srcs/mandatory/parsing/get_color.c \
		srcs/mandatory/parsing/check_order_textures.c \

SRCSB = srcs/bonus/main_bonus.c \
		srcs/bonus/raycasting/init_bonus.c \
		srcs/bonus/raycasting/player_move_bonus.c \
		srcs/bonus/raycasting/raycasting_utils_bonus.c \
		srcs/bonus/raycasting/raycasting_bonus.c \
		srcs/bonus/raycasting/rendering_bonus.c \
		srcs/bonus/raycasting/rendering_utils_bonus.c \
		srcs/bonus/raycasting/normalize_bonus.c \
		srcs/bonus/raycasting/wall_collision_bonus.c \
		srcs/bonus/raycasting/cleanup_bonus.c \
		srcs/bonus/raycasting/launch_bonus.c \
		\
		srcs/bonus/parsing/check_file_name_bonus.c \
		srcs/bonus/parsing/helper-functions/custom_error_bonus.c \
		srcs/bonus/parsing/check_map_bonus.c \
		libraries/get_next_line/get_next_line.c \
		srcs/bonus/parsing/check_color_bonus.c \
		srcs/bonus/parsing/check_num_of_players_bonus.c \
		srcs/bonus/parsing/map_is_valid_bonus.c \
		srcs/bonus/parsing/get_color_bonus.c \
		srcs/bonus/parsing/check_order_textures_bonus.c \

LIBFT_DIR = ./libraries/libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = ./libraries/minilibx-linux
MLX_LIB = ./libraries/minilibx-linux/libmlx.a

OBJS = $(SRCS:.c=.o)
OBJSB = $(SRCSB:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
MLX_FLAGS = -lmlx -lXext -lX11 -lm -lz
RM = rm -f

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(MLX_FLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX_LIB)

$(NAMEB): $(OBJSB) $(LIBFT)
	$(CC) $(CFLAGS) $(MLX_FLAGS) -o $(NAMEB) $(OBJSB) $(LIBFT) $(MLX_LIB)

$(LIBFT):
	make bonus -C $(LIBFT_DIR)

all: $(NAME)

bonus: $(NAMEB)

run: bonus
	${RM} ${OBJSB}
	./cub3d_bonus	./maps/map_1.cub

clean:
	$(RM) $(OBJS) $(OBJSB)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME) $(NAMEB)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: ${OBJS} $(OBJSB)