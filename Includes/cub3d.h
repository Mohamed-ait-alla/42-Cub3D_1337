/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:09:20 by mait-all          #+#    #+#             */
/*   Updated: 2025/08/04 15:47:45 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# ifndef PI
#  define PI 3.141592653589793238462
# endif
# define TILE_SIZE 32
# define MAP_NUM_ROWS 16
# define MAP_NUM_COLS 20
# define WINDOW_WIDTH MAP_NUM_COLS * TILE_SIZE
# define WINDOW_HEIGHT MAP_NUM_ROWS * TILE_SIZE
# define FOV 60 * (PI / 180)
# define NUM_RAYS WINDOW_WIDTH
# define TEXTURE_WIDTH 32
# define TEXTURE_HIEGHT 32
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <string.h>
# include <X11/keysym.h>
# include "../libraries/minilibx-linux/mlx.h"
# include "../libraries/libft/libft.h"


typedef struct s_player {
	float	player_x;
	float	player_y;
	float	dir_x;
	float	dir_y;
	int		turn_dir;
	int		walk_dir;
	double		rotation_Angle;
	int		move_speed;
	int		rotation_speed;
}	t_player;

typedef	struct s_ray
{
	double	ray_angle;
	double	ray_distored_distance;
	double	ray_correct_distance;
	int		was_hit_horz;
	int		was_hit_vert;
	double	wall_hit_x;
	double	wall_hit_y;
}	t_ray;

typedef struct s_texture 
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_texture;


typedef struct  s_mlx_data
{
	void	*mlx_ptr;
	void	*mlx_window;
	void	*img;
	char	*img_pixels;
	int		bpp;
	int		size_line;
	int		endian;
	t_texture	wall_texture;
	t_player	player;
	t_ray		rays[NUM_RAYS];
}	t_mlx_data;


// #-------------- raycasting prototypes --------------#
void	init_player(t_mlx_data *mlx);
int		ft_destroy_window(t_mlx_data *mlx);
int		key_Pressed(int keycode, t_mlx_data *mlx);
int		is_wall(float x, float y);
void	put_pixel(t_mlx_data *mlx, int x, int y, int color);
void	draw_circle(t_mlx_data *mlx, int cx, int cy, int radius, int color);
void	draw_square(t_mlx_data *mlx, int x, int y, int color);
void	draw_line(t_mlx_data *mlx, int x0, int y0, int x1, int y1, int color);
void	draw_facing_line(t_mlx_data *mlx, double length, double color);
void	render(t_mlx_data *mlx);
int		update(t_mlx_data *mlx);
void	cast_rays(t_mlx_data *mlx);

int	load_wall_texture(t_mlx_data *mlx, char *path);

#endif