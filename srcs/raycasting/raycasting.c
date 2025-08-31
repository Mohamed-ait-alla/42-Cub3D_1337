/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 10:54:38 by mait-all          #+#    #+#             */
/*   Updated: 2025/08/30 18:35:11 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	normalize_angle(double angle)
{
	angle = fmod(angle, (2 * M_PI));
	if (angle < 0)
		angle += (2 * M_PI);
	return (angle);
}

double get_distance_between_points(double x0, double y0, double x1, double y1)
{
	return (sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0)));
}

void	get_smallest_distance(t_mlx_data *mlx, int i,
								double found_horz_wall_hit, double found_vert_wall_hit,
								double horz_wall_hit_x, double horz_wall_hit_y,
								double vert_wall_hit_x, double vert_wall_hit_y)
{
	double	horz_hit_distance;
	double	vert_hit_distance;

	mlx->rays[i].was_hit_horz = 0;
	mlx->rays[i].was_hit_vert = 0;
	if (found_horz_wall_hit)
		horz_hit_distance = get_distance_between_points(mlx->player.px, mlx->player.py, horz_wall_hit_x, horz_wall_hit_y);
	else
		horz_hit_distance = 2147483647;
	if (found_vert_wall_hit)
		vert_hit_distance = get_distance_between_points(mlx->player.px, mlx->player.py, vert_wall_hit_x, vert_wall_hit_y);
	else
		vert_hit_distance = 2147483647;
	// store values
	if (horz_hit_distance < vert_hit_distance)
	{
		mlx->rays[i].wall_hit_x = horz_wall_hit_x;
		mlx->rays[i].wall_hit_y = horz_wall_hit_y;
		mlx->rays[i].ray_distored_distance = horz_hit_distance;
		mlx->rays[i].was_hit_horz = 1;
	}
	else
	{
		mlx->rays[i].wall_hit_x = vert_wall_hit_x;
		mlx->rays[i].wall_hit_y = vert_wall_hit_y;
		mlx->rays[i].ray_distored_distance = vert_hit_distance;
		mlx->rays[i].was_hit_vert = 1;
	}
	mlx->rays[i].ray_correct_distance = mlx->rays[i].ray_distored_distance * cos(mlx->rays[i].ray_angle - mlx->player.rotation_Angle);
}

int	is_ray_facing_down(double ray_angle)
{
	return (ray_angle > 0 && ray_angle < M_PI);
}

int is_ray_facing_right(double ray_angle)
{
	return (ray_angle < 0.5 * M_PI || ray_angle > 1.5 * M_PI);
}

int	find_horizontal_intersection(t_mlx_data *mlx, double *horz_wall_hit_x, double *horz_wall_hit_y, double ray_angle)
{
	double	x_intercept;
	double	y_intercept;
	double	x_step;
	double	y_step;

	// find the y-coordinate of the closest horizontal grid intersection
	y_intercept = floor(mlx->player.py / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_down(ray_angle))
		y_intercept += TILE_SIZE;
	// find the x-coordinate of the closest horizontal grid intersection
	x_intercept = mlx->player.px + (y_intercept - mlx->player.py) / tan(ray_angle);
	
	// caluculate the increment of the closest horizontal xstep and ystep
	y_step = TILE_SIZE;
	if (!is_ray_facing_down(ray_angle)) // if ray is facing up
		y_step *= -1;
	
	x_step = TILE_SIZE / tan(ray_angle);
	if (!is_ray_facing_right(ray_angle) && x_step > 0)
		x_step *= -1;
	else if (is_ray_facing_right(ray_angle) && x_step < 0)
		x_step *= -1;

	while (x_intercept >= 0 && x_intercept <= WINDOW_WIDTH && y_intercept >= 0 && y_intercept <= WINDOW_HEIGHT)
	{
		if (is_wall(mlx, x_intercept , y_intercept - (!is_ray_facing_down(ray_angle) ? 1 : 0)))
		{
			// we hit the wall
			*horz_wall_hit_x = x_intercept;
			*horz_wall_hit_y = y_intercept;
			return (1);
		}
		x_intercept += x_step;
		y_intercept += y_step;
	}
	return (0);
}

int	find_vertical_intersections(t_mlx_data *mlx, double *vert_wall_hit_x, double *vert_wall_hit_y, double ray_angle)
{
	double	x_intercept;
	double	y_intercept;
	double	x_step;
	double	y_step;

	x_intercept = floor(mlx->player.px / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_right(ray_angle))
		x_intercept += TILE_SIZE;
	// find the x-coordinate of the closest vertical grid intersection
	y_intercept = mlx->player.py + (x_intercept - mlx->player.px) * tan(ray_angle);
	
	// calculate the increment xstep and ystep (deltax, deltay)
	x_step = TILE_SIZE;
	if (!is_ray_facing_right(ray_angle)) // is ray facing left
	 	x_step *= -1;
	y_step = TILE_SIZE * tan(ray_angle);
	if (!is_ray_facing_down(ray_angle) && y_step > 0)
		y_step *= -1;
	else if (is_ray_facing_down(ray_angle) && y_step < 0)
		y_step *= -1;
	
	while (x_intercept >= 0 && x_intercept <= WINDOW_WIDTH && y_intercept >= 0 && y_intercept <= WINDOW_HEIGHT)
	{
		if (is_wall(mlx, x_intercept - (!is_ray_facing_right(ray_angle) ? 1 : 0), y_intercept))
		{
			*vert_wall_hit_x = x_intercept;
			*vert_wall_hit_y = y_intercept;
			return (1);
		}
		x_intercept += x_step;
		y_intercept += y_step;
	}
	return (0);
}

void	cast(t_mlx_data *mlx, int i)
{
	double	horz_wall_hit_x;
	double	horz_wall_hit_y;
	double	vert_wall_hit_x;
	double	vert_wall_hit_y;
	double	found_horz_wall_hit;
	double	found_vert_wall_hit;
	double	ray_angle;

	ray_angle = normalize_angle(mlx->rays[i].ray_angle);
	mlx->rays[i].ray_angle = ray_angle;
	mlx->ray_angle = ray_angle;
	// ------------ find horizontal interception -------------
	found_horz_wall_hit = find_horizontal_intersection(mlx, &horz_wall_hit_x, &horz_wall_hit_y, ray_angle);

	// ------------ find vertical interception -------------
	found_vert_wall_hit = find_vertical_intersections(mlx, &vert_wall_hit_x, &vert_wall_hit_y, ray_angle);
	// calculate both horz and vert distances and choose the smallest value
	get_smallest_distance(mlx, i, found_horz_wall_hit, found_vert_wall_hit,
							horz_wall_hit_x, horz_wall_hit_y, vert_wall_hit_x,
							vert_wall_hit_y);
	// draw_line(mlx, mlx->player.px, mlx->player.py, mlx->rays[i].wall_hit_x, mlx->rays[i].wall_hit_y, 0xfff000);
}

void	cast_rays(t_mlx_data *mlx)
{
	int	i = 0;

	mlx->rays[0].ray_angle = mlx->player.rotation_Angle - (FOV / 2);
	while (i < NUM_RAYS)
	{
		cast(mlx, i);
		i++;
		mlx->rays[i].ray_angle = mlx->rays[i - 1].ray_angle + FOV / (NUM_RAYS);
	}
}
