/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:09:20 by mait-all          #+#    #+#             */
/*   Updated: 2025/09/07 14:28:32 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# ifndef M_PI
#  define M_PI 3.141592653589793238462
# endif
# define MAX_DOORS 10
# define TILE_SIZE 32
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define NUM_RAYS WINDOW_WIDTH
# define FOV 60 * (M_PI / 180)
# include "../libraries/libft/libft.h"
# include "../libraries/minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <sys/time.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_door {
	int	x;
	int	y;
	int	is_open;
}	t_door;

typedef struct s_player
{
	int			anim_index;
	int			is_animating;
	double		px;
	double		py;
	double		rotation_Angle;
	double		move_speed;
}				t_player;

typedef struct s_ray
{
	double		ray_angle;
	double		ray_distored_distance;
	double		ray_correct_distance;
	int			was_hit_horz;
	int			was_hit_vert;
	int			was_hit_door;
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
	int			key_esc;
	int			key_space;
}				t_keys;

typedef struct s_map
{
	int			_0;
	int			_1;
	int			_N;
	int			_S;
	int			_E;
	int			_W;
	int			_D;
	int			num_NO;
	int			num_SO;
	int			num_WE;
	int			num_EA;
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
	bool		ORDER_NO;
	bool		ORDER_SO;
	bool		ORDER_WE;
	bool		ORDER_EA;
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
	int			doors_count;
	double		px_player;
	double		py_player;
	char		player;
	t_door		doors[MAX_DOORS];
}				t_map;


typedef struct s_mlx_data
{
	void		*mlx_ptr;
	void		*mlx_window;
	void		*img;
	char		*img_pixels;
	char		tile;
	int			bpp;
	int			size_line;
	int			endian;
	int			wall_top;
	int			wall_bottom;
	int			horz_hit_door;
	int			vert_hit_door;
	double		dx;
	double		dy;
	double		door_world_x;
	double		door_world_y;
	double		horz_wall_hit_x;
	double		horz_wall_hit_y;
	double		vert_wall_hit_x;
	double		vert_wall_hit_y;
	t_keys		keys;
	t_texture	textures[10];
	t_texture	*wall_texture;
	t_player	player;
	t_ray		rays[NUM_RAYS];
	t_map		map;
}				t_mlx_data;

// #-------------- raycasting prototypes --------------#
void 			launch(t_mlx_data *mlx);
int				ft_cleanup(t_mlx_data *mlx);
void			init_player(t_mlx_data *mlx, t_map *map);
int				key_pressed(int keycode, t_mlx_data *mlx);
int				key_released(int keycode, t_mlx_data *mlx);
void			update_player_position(t_mlx_data *mlx);
int				is_wall(t_mlx_data *mlx, double x, double y);
int				has_collision(t_mlx_data *mlx, float x, float y);
void			put_pixel(t_mlx_data *mlx, int x, int y, int color);
int				update(t_mlx_data *mlx);
void			cast_rays(t_mlx_data *mlx);
int				is_ray_facing_down(double ray_angle);
int 			is_ray_facing_right(double ray_angle);
void			*ft_malloc(size_t size, int mode);
double			normalize_angle(double angle);
double			 get_distance_between_points(double x0, double y0,
												double x1, double y1);
double 			normalize_x_axis(double x, double ray_angle);
double 			normalize_y_axis(double y, double ray_angle);
double 			normalize_diff_door_player_angle(double angle);
void			set_rays_to_walls_distance(t_mlx_data *mlx, int i,
								double horz_hit_distance,
								double vert_hit_distance);
int				get_texture_pixel(t_mlx_data *mlx, int x, int y);
t_texture		*get_wall_texture(t_mlx_data *mlx, int x);
void			toggle_door(t_mlx_data *mlx);
t_door			*find_closest_door(t_mlx_data *mlx);
void			reset(t_mlx_data *mlx, int i);
int				set_horz_wall_hit(t_mlx_data *mlx, double x_intercept, double y_intercept);
int				set_vert_wall_hit(t_mlx_data *mlx, double x_intercept, double y_intercept);
void			put_gun(t_mlx_data *mlx, int start_x, int start_y, int anim_index);
void			render_gun(t_mlx_data *mlx);
double			get_time();
void			update_player_animation(t_mlx_data *mlx);

// #--------------- Parsing map ----------------#

bool			check_file_name(char *file_name);
int				custom_error(t_mlx_data *mlx, char *msg);
bool			check_map(char *file, t_map *map);
char			*get_next_line(int fd);
bool			check_color(t_map *map);
bool			check_num_of_players(t_map *map);
bool 			map_is_valid(t_map *map);
void			get_color(t_map *map);
bool			check_order_textures(t_map *map);

#endif