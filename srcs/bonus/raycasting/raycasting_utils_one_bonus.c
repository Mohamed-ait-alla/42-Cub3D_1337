/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils_one_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:48:52 by mait-all          #+#    #+#             */
/*   Updated: 2025/09/12 11:46:48 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

void	setup_flags(t_mlx_data *mlx, int i, char type)
{
	if (type == 'h')
	{
		if (mlx->horz_hit_door)
		{
			mlx->rays[i].was_hit_door = 1;
			mlx->rays[i].door_hit_direction = 0;
		}
		else
			mlx->rays[i].was_hit_horz = 1;
	}
	if (type == 'v')
	{
		if (mlx->vert_hit_door)
		{
			mlx->rays[i].was_hit_door = 1;
			mlx->rays[i].door_hit_direction = 1;
		}
		else
			mlx->rays[i].was_hit_vert = 1;
	}
}

void	set_rays_to_walls_distance(t_mlx_data *mlx, int i,
								double horz_hit_distance,
								double vert_hit_distance)
{
	if (horz_hit_distance < vert_hit_distance)
	{
		mlx->rays[i].wall_hit_x = mlx->horz_wall_hit_x;
		mlx->rays[i].wall_hit_y = mlx->horz_wall_hit_y;
		mlx->rays[i].ray_distored_distance = horz_hit_distance;
		setup_flags(mlx, i, 'h');
	}
	else
	{
		mlx->rays[i].wall_hit_x = mlx->vert_wall_hit_x;
		mlx->rays[i].wall_hit_y = mlx->vert_wall_hit_y;
		mlx->rays[i].ray_distored_distance = vert_hit_distance;
		setup_flags(mlx, i, 'v');
	}
	mlx->rays[i].ray_correct_distance = mlx->rays[i].ray_distored_distance
		* cos(mlx->rays[i].ray_angle - mlx->player.rotation_angle);
}

double	get_distance_between_points(double x0, double y0, double x1, double y1)
{
	return (sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0)));
}

int	is_ray_facing_down(double ray_angle)
{
	return (ray_angle > 0 && ray_angle < M_PI);
}

int	is_ray_facing_right(double ray_angle)
{
	return (ray_angle < 0.5 * M_PI || ray_angle > 1.5 * M_PI);
}
