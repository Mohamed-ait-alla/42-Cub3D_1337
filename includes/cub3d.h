/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:09:20 by mait-all          #+#    #+#             */
/*   Updated: 2025/08/29 10:59:46 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# ifndef M_PI
#  define M_PI 3.141592653589793238462
# endif
# define TILE_SIZE 32
# define MAP_NUM_ROWS 16
# define MAP_NUM_COLS 20
# define WINDOW_WIDTH MAP_NUM_COLS *TILE_SIZE
# define WINDOW_HEIGHT MAP_NUM_ROWS *TILE_SIZE
# define FOV 60 * (M_PI / 180)
# define NUM_RAYS WINDOW_WIDTH
# include "../libraries/libft/libft.h"
# include "../libraries/minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_player
{
	double		px;
	double		py;
	int			turn_dir;
	int			walk_dir;
	double		rotation_Angle;
	double			move_speed;
	int			rotation_speed;
}				t_player;

typedef struct s_ray
{
	double		ray_angle;
	double		ray_distored_distance;
	double		ray_correct_distance;
	int			was_hit_horz;
	int			was_hit_vert;
	double		wall_hit_x;
	double		wall_hit_y;
}				t_ray;

typedef struct s_texture
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_texture;

typedef struct s_keys
{
	int			key_w;
	int			key_s;
	int			key_d;
	int			key_a;
	int			key_left;
	int			key_right;
	int			key_escape;
}				t_keys;

typedef struct s_map
{
	int			_0;
	int			_1;
	int			_N;
	int			_S;
	int			_E;
	int			_W;
	int			num_NO;
	int			num_SO;
	int			num_WE;
	int			num_EA;
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
	char		*f_color;
	char		*c_color;
	int			num_f_color;
	int			num_c_color;
	char		**map;
	char		**copy_map;
	int			rows;
	int			cols;
	int			floor_color;
	int			ceiling_color;
	double		px_player;
	double		py_player;
	char		player;
}				t_map;


typedef struct s_mlx_data
{
	void		*mlx_ptr;
	void		*mlx_window;
	void		*img;
	char		*img_pixels;
	int			bpp;
	int			size_line;
	int			endian;
	double		ray_angle;
	t_keys		keys;
	t_texture	wall_texture;
	t_player	player;
	t_ray		rays[NUM_RAYS];
	t_map		map;
}				t_mlx_data;

// #-------------- raycasting prototypes --------------#
void			init_player(t_mlx_data *mlx);
int				ft_destroy_window(t_mlx_data *mlx);
int				key_pressed(int keycode, t_mlx_data *mlx);
int				key_released(int keycode, t_mlx_data *mlx);
void			update_player_position(t_mlx_data *mlx);
int				is_wall(t_mlx_data *mlx, double x, double y);
void			put_pixel(t_mlx_data *mlx, int x, int y, int color);
void			draw_circle(t_mlx_data *mlx, int cx, int cy, int radius,
					int color);
void			draw_square(t_mlx_data *mlx, int x, int y, int color);
void			draw_line(t_mlx_data *mlx, int x0, int y0, int x1, int y1,
					int color);
void			draw_facing_line(t_mlx_data *mlx, double length, double color);
void			render(t_mlx_data *mlx);
int				update(t_mlx_data *mlx);
void			cast_rays(t_mlx_data *mlx);
int				load_wall_texture(t_mlx_data *mlx, char *path);
int				is_ray_facing_down(double ray_angle);
int 			is_ray_facing_right(double ray_angle);

// #--------------- Parsing map ----------------#

bool			check_file_name(char *file_name);
void			custom_error(char *msg);
bool			check_map(char *file, t_map *map);
char			*get_next_line(int fd);
bool			check_color(t_map *map);
bool			check_num_of_players(t_map *map);
bool 			map_is_valid(t_map *map);
void			get_color(t_map *map);

#endif