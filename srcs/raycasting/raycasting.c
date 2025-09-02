/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 10:54:38 by mait-all          #+#    #+#             */
/*   Updated: 2025/09/02 10:18:48 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	set_rays_to_walls_distance(t_mlx_data *mlx, int i,
								double horz_hit_distance,
								double vert_hit_distance)
{
	if (horz_hit_distance < vert_hit_distance)
	{
		mlx->rays[i].wall_hit_x = mlx->horz_wall_hit_x;
		mlx->rays[i].wall_hit_y = mlx->horz_wall_hit_y;
		mlx->rays[i].ray_distored_distance = horz_hit_distance;
		mlx->rays[i].was_hit_horz = 1;
	}
	else
	{
		mlx->rays[i].wall_hit_x = mlx->vert_wall_hit_x;
		mlx->rays[i].wall_hit_y = mlx->vert_wall_hit_y;
		mlx->rays[i].ray_distored_distance = vert_hit_distance;
		mlx->rays[i].was_hit_vert = 1;
	}
	mlx->rays[i].ray_correct_distance = mlx->rays[i].ray_distored_distance *
						cos(mlx->rays[i].ray_angle - mlx->player.rotation_Angle);
}

void	calculate_ray_intersection_steps(double *x_step, double *y_step, double ray_angle, char type)
{
	if (type == 'h')
	{
		*y_step = TILE_SIZE;
		if (!is_ray_facing_down(ray_angle))
			*y_step *= -1;
		*x_step = TILE_SIZE / tan(ray_angle);
		if (!is_ray_facing_right(ray_angle) && *x_step > 0)
			*x_step *= -1;
		else if (is_ray_facing_right(ray_angle) && *x_step < 0)
			*x_step *= -1;
	}
	if (type == 'v')
	{
		*x_step = TILE_SIZE;
		if (!is_ray_facing_right(ray_angle))
			*x_step *= -1;
		*y_step = TILE_SIZE * tan(ray_angle);
		if (!is_ray_facing_down(ray_angle) && *y_step > 0)
			*y_step *= -1;
		else if (is_ray_facing_down(ray_angle) && *y_step < 0)
			*y_step *= -1;
	}
}

int	find_horizontal_intersection(t_mlx_data *mlx, double ray_angle)
{
	double	x_intercept;
	double	y_intercept;
	double	x_step;
	double	y_step;

	y_intercept = floor(mlx->player.py / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_down(ray_angle))
		y_intercept += TILE_SIZE;
	x_intercept = mlx->player.px + (y_intercept - mlx->player.py) / tan(ray_angle);
	calculate_ray_intersection_steps(&x_step, &y_step, ray_angle, 'h');
	while (x_intercept >= 0 && x_intercept <= mlx->window_width && y_intercept >= 0 && y_intercept <= mlx->window_height)
	{
		if (is_wall(mlx, x_intercept , normalize_y_axis(y_intercept, ray_angle)))
		{
			mlx->horz_wall_hit_x = x_intercept;
			mlx->horz_wall_hit_y = y_intercept;
			return (1);
		}
		x_intercept += x_step;
		y_intercept += y_step;
	}
	return (0);
}

int	find_vertical_intersections(t_mlx_data *mlx, double ray_angle)
{
	double	x_intercept;
	double	y_intercept;
	double	x_step;
	double	y_step;

	x_intercept = floor(mlx->player.px / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_right(ray_angle))
		x_intercept += TILE_SIZE;
	y_intercept = mlx->player.py + (x_intercept - mlx->player.px) * tan(ray_angle);
	calculate_ray_intersection_steps(&x_step, &y_step, ray_angle, 'v');
	while (x_intercept >= 0 && x_intercept <= mlx->window_width && y_intercept >= 0 && y_intercept <= mlx->window_height)
	{
		if (is_wall(mlx, normalize_x_axis(x_intercept, ray_angle), y_intercept))
		{
			mlx->vert_wall_hit_x = x_intercept;
			mlx->vert_wall_hit_y = y_intercept;
			return (1);
		}
		x_intercept += x_step;
		y_intercept += y_step;
	}
	return (0);
}

void	cast(t_mlx_data *mlx, int i)
{
	double	found_horz_wall_hit;
	double	found_vert_wall_hit;
	double	horz_hit_distance;
	double	vert_hit_distance;
	double	ray_angle;

	mlx->rays[i].was_hit_horz = 0;
	mlx->rays[i].was_hit_vert = 0;
	ray_angle = normalize_angle(mlx->rays[i].ray_angle);
	mlx->rays[i].ray_angle = ray_angle;
	found_horz_wall_hit = find_horizontal_intersection(mlx, ray_angle);
	found_vert_wall_hit = find_vertical_intersections(mlx, ray_angle);
	if (found_horz_wall_hit)
		horz_hit_distance = get_distance_between_points(mlx->player.px,
						mlx->player.py, mlx->horz_wall_hit_x, mlx->horz_wall_hit_y);
	else
		horz_hit_distance = 2147483647;
	if (found_vert_wall_hit)
		vert_hit_distance = get_distance_between_points(mlx->player.px,
				mlx->player.py, mlx->vert_wall_hit_x, mlx->vert_wall_hit_y);
	else
		vert_hit_distance = 2147483647;
	set_rays_to_walls_distance(mlx, i, horz_hit_distance, vert_hit_distance);
}

void	cast_rays(t_mlx_data *mlx)
{
	int	i = 0;
	double r_angle;

	r_angle = mlx->player.rotation_Angle - (FOV / 2);
	while (i < mlx->nb_rays)
	{
		mlx->rays[i].ray_angle = r_angle;
		cast(mlx, i);
		r_angle += (FOV / mlx->nb_rays);
		i++;
	}
}
