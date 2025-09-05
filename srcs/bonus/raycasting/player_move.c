/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 10:06:57 by mait-all          #+#    #+#             */
/*   Updated: 2025/09/05 08:19:16 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"
int	is_near(t_mlx_data *mlx)
{
    double door_world_x = mlx->map.door.x * TILE_SIZE + TILE_SIZE / 2;
    double door_world_y = mlx->map.door.y * TILE_SIZE + TILE_SIZE / 2;

	double distance;
	
	distance = sqrt(pow(mlx->player.px - door_world_x, 2) + pow(mlx->player.py - door_world_y, 2));
	return (distance <= 70);
}

int	key_pressed(int keycode, t_mlx_data *mlx)
{
	if (keycode == XK_Escape)
		mlx->keys.key_esc = 1;
	if (keycode == XK_space)
	{
		if (is_near(mlx))
		{
			if (mlx->map.door.is_open)
			{
				mlx->map.door.is_open = 0;
				mlx->map.map[mlx->map.door.y][mlx->map.door.x] = 'D';
			}
			else if (!mlx->map.door.is_open)
			{
				mlx->map.door.is_open = 1;
				mlx->map.map[mlx->map.door.y][mlx->map.door.x] = '0';
			}
		}
	}
	if (keycode == XK_Left)
		mlx->keys.key_left = 1;
	if (keycode == XK_Right)
		mlx->keys.key_right = 1;
	if (keycode == XK_a)
		mlx->keys.key_a = 1;
	if (keycode == XK_d)
		mlx->keys.key_d = 1;
	if (keycode == XK_w)
		mlx->keys.key_w = 1;
	if (keycode == XK_s)
		mlx->keys.key_s = 1;
	return (0);
}

int	key_released(int keycode, t_mlx_data *mlx)
{
	if (keycode == XK_Escape)
		mlx->keys.key_esc = 0;
	if (keycode == XK_space)
		mlx->keys.key_space = 0;
	if (keycode == XK_Left)
		mlx->keys.key_left = 0;
	if (keycode == XK_Right)
		mlx->keys.key_right = 0;
	if (keycode == XK_a)
		mlx->keys.key_a = 0;
	if (keycode == XK_d)
		mlx->keys.key_d = 0;
	if (keycode == XK_w)
		mlx->keys.key_w = 0;
	if (keycode == XK_s)
		mlx->keys.key_s = 0;
	return (0);
}

void	setup_player_position(t_mlx_data *mlx, float *next_x, float *next_y)
{
	if (mlx->keys.key_w)
	{
		*next_x += cos(mlx->player.rotation_Angle) * mlx->player.move_speed;
		*next_y += sin(mlx->player.rotation_Angle) * mlx->player.move_speed;
	}
	if (mlx->keys.key_s)
	{
		*next_x -= cos(mlx->player.rotation_Angle) * mlx->player.move_speed;
		*next_y -= sin(mlx->player.rotation_Angle) * mlx->player.move_speed;
	}
	if (mlx->keys.key_a)
	{
		*next_x += sin(mlx->player.rotation_Angle) * mlx->player.move_speed;
		*next_y -= cos(mlx->player.rotation_Angle) * mlx->player.move_speed;
	}
	if (mlx->keys.key_d)
	{
		*next_x -= sin(mlx->player.rotation_Angle) * mlx->player.move_speed;
		*next_y += cos(mlx->player.rotation_Angle) * mlx->player.move_speed;
	}
}

void	update_player_position(t_mlx_data *mlx)
{
	float	next_x;
	float	next_y;

	next_x = mlx->player.px;
	next_y = mlx->player.py;
	if (mlx->keys.key_esc)
		ft_cleanup(mlx);
	if (mlx->keys.key_right)
		mlx->player.rotation_Angle += 0.005;
	if (mlx->keys.key_left)
		mlx->player.rotation_Angle -= 0.005;
	setup_player_position(mlx, &next_x, &next_y);
	if (!has_collision(mlx, next_x, next_y))
	{
		mlx->player.px = next_x;
		mlx->player.py = next_y;
	}
}
