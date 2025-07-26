/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:09:20 by mait-all          #+#    #+#             */
/*   Updated: 2025/07/26 12:58:18 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# ifndef PI
#  define PI 3.141592653589793238462
# endif
# define TILE_SIZE 32
# define MAP_NUM_ROWS 6
# define MAP_NUM_COLS 8
# define WINDOW_WIDTH MAP_NUM_COLS * TILE_SIZE
# define WINDOW_HEIGHT MAP_NUM_ROWS * TILE_SIZE
# define FOV 60 * (PI / 180)
# define NUM_RAYS WINDOW_WIDTH
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


typedef struct  s_mlx_data
{
	void	*mlx_ptr;
	void	*mlx_window;
	void	*img;
	char	*img_pixels;
	int		bpp;
	int		size_line;
	int		endian;
	t_player	player;
}	t_mlx_data;


#endif