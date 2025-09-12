/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_doors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 12:56:16 by mait-all          #+#    #+#             */
/*   Updated: 2025/09/12 10:32:30 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

double	get_door_player_angle(t_mlx_data *mlx, int i)
{
	double	door_angle;
	double	diff_angle;

	mlx->door_world_x = mlx->map.doors[i].x * TILE_SIZE + (TILE_SIZE / 2);
	mlx->door_world_y = mlx->map.doors[i].y * TILE_SIZE + (TILE_SIZE / 2);
	mlx->dx = mlx->door_world_x - mlx->player.px;
	mlx->dy = mlx->door_world_y - mlx->player.py;
	door_angle = atan2(mlx->dy, mlx->dx);
	diff_angle = door_angle - mlx->player.rotation_angle;
	diff_angle = normalize_diff_door_player_angle(diff_angle);
	return (diff_angle);
}

t_door	*find_closest_door(t_mlx_data *mlx)
{
	t_door	*closest_door;
	double	min_distance;
	double	distance;
	double	diff_angle;
	int		i;

	closest_door = NULL;
	min_distance = 70;
	i = 0;
	while (i < mlx->map.doors_count)
	{
		diff_angle = get_door_player_angle(mlx, i);
		distance = sqrt(mlx->dx * mlx->dx + mlx->dy * mlx->dy);
		if (fabs(diff_angle) <= (FOV / 2) && distance < min_distance)
		{
			min_distance = distance;
			closest_door = &mlx->map.doors[i];
		}
		i++;
	}
	return (closest_door);
}

void	toggle_door(t_mlx_data *mlx)
{
	t_door	*door;
	int		p_tile_x;
	int		p_tile_y;

	p_tile_x = (int)(mlx->player.px / TILE_SIZE);
	p_tile_y = (int)(mlx->player.py / TILE_SIZE);
	door = find_closest_door(mlx);
	if (door)
	{
		if (door->is_open)
		{
			if (p_tile_x != door->x || p_tile_y != door->y)
			{
				door->is_open = 0;
				mlx->map.map[door->y][door->x] = 'D';
			}
		}
		else if (!door->is_open)
		{
			door->is_open = 1;
			mlx->map.map[door->y][door->x] = '0';
		}
	}
	else
		return ;
}
