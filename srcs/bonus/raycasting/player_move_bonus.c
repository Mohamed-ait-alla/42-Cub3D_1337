/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 10:06:57 by mait-all          #+#    #+#             */
/*   Updated: 2025/09/05 18:55:19 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"
int	is_near(t_mlx_data *mlx)
{
    double door_world_x = mlx->map.doors[0].x * TILE_SIZE + TILE_SIZE / 2;
    double door_world_y = mlx->map.doors[0].y * TILE_SIZE + TILE_SIZE / 2;

	double distance;
	
	distance = sqrt(pow(mlx->player.px - door_world_x, 2) + pow(mlx->player.py - door_world_y, 2));
	return (distance <= 70);
}

t_door	*find_closest_door(t_mlx_data *mlx)
{
	t_door	*closest_door = NULL;
	double	min_distance = 70;
	double	distance;
	double	door_world_x;
	double	door_world_y;
	double	dx, dy, door_angle, diff_angle;
	int		i;

	i = 0;
	while (i < mlx->map.doors_count)
	{
		door_world_x = mlx->map.doors[i].x * TILE_SIZE + (TILE_SIZE / 2);
		door_world_y = mlx->map.doors[i].y * TILE_SIZE + (TILE_SIZE / 2);
		dx = door_world_x - mlx->player.px;
		dy = door_world_y - mlx->player.py;

		distance = sqrt(dx * dx + dy * dy);
		door_angle = atan2(dy, dx);
		diff_angle = door_angle - mlx->player.rotation_Angle;
		diff_angle = normalize_diff_door_player_angle(diff_angle);
		if (fabs(diff_angle) <= (FOV / 2) && distance < min_distance)
		{
			min_distance = distance;
			closest_door = &mlx->map.doors[i];
		}
		i++;
	}
	return (closest_door);
}


int	key_pressed(int keycode, t_mlx_data *mlx)
{
	if (keycode == XK_Escape)
		mlx->keys.key_esc = 1;
	if (keycode == XK_space)
	{
		t_door	*door;

		door = find_closest_door(mlx);
		if (door)
		{
			if (door->is_open)
			{
				door->is_open = 0;
				mlx->map.map[door->y][door->x] = 'D';
			}
			else if (!door->is_open)
			{
				door->is_open = 1;
				mlx->map.map[door->y][door->x] = '0';
			}
		}
		else
			return (0);
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
