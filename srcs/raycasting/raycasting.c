/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 10:54:38 by mait-all          #+#    #+#             */
/*   Updated: 2025/08/18 10:12:28 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	normalize_angle(double angle)
{
	angle = fmod(angle, (2 * PI));
	if (angle < 0)
		angle += (2 * PI);
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
	double	wall_hit_x;
	double	wall_hit_y;
	double	horz_hit_distance;
	double	vert_hit_distance;

	mlx->rays[i].was_hit_horz = 0;
	mlx->rays[i].was_hit_vert = 0;
	if (found_horz_wall_hit)
		horz_hit_distance = get_distance_between_points(mlx->player.player_x, mlx->player.player_y, horz_wall_hit_x, horz_wall_hit_y);
	else
		horz_hit_distance = 2147483647;
	if (found_vert_wall_hit)
		vert_hit_distance = get_distance_between_points(mlx->player.player_x, mlx->player.player_y, vert_wall_hit_x, vert_wall_hit_y);
	else
		vert_hit_distance = 2147483647;
	// store values
	if (horz_hit_distance < vert_hit_distance)
	{
		wall_hit_x = horz_wall_hit_x;
		wall_hit_y = horz_wall_hit_y;
		mlx->rays[i].wall_hit_x = wall_hit_x;
		mlx->rays[i].wall_hit_y = wall_hit_y;
		mlx->rays[i].ray_distored_distance = horz_hit_distance;
		mlx->rays[i].was_hit_horz = 1;
	}
	else
	{
		wall_hit_x = vert_wall_hit_x;
		wall_hit_y = vert_wall_hit_y;
		mlx->rays[i].wall_hit_x = wall_hit_x;
		mlx->rays[i].wall_hit_y = wall_hit_y;
		mlx->rays[i].ray_distored_distance = vert_hit_distance;
		mlx->rays[i].was_hit_vert = 1;
	}
	mlx->rays[i].ray_correct_distance = mlx->rays[i].ray_distored_distance * cos(mlx->rays[i].ray_angle - mlx->player.rotation_Angle);
}

int	is_ray_facing_down(double ray_angle)
{
	return (ray_angle > 0 && ray_angle < PI);
}

int is_ray_facing_right(double ray_angle)
{
	return (ray_angle < 0.5 * PI || ray_angle > 1.5 * PI);
}

int	find_horizontal_intersection(t_mlx_data *mlx, double *horz_wall_hit_x, double *horz_wall_hit_y, double ray_angle)
{
	double	x_intercept;
	double	y_intercept;
	double	x_step;
	double	y_step;
	double	next_horz_touch_x;
	double	next_horz_touch_y;

	// find the y-coordinate of the closest horizontal grid intersection
	y_intercept = floor(mlx->player.player_y / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_down(ray_angle))
		y_intercept += TILE_SIZE;
	// find the x-coordinate of the closest horizontal grid intersection
	x_intercept = mlx->player.player_x + (y_intercept - mlx->player.player_y) / tan(ray_angle);
	
	// caluculate the increment of the closest horizontal xstep and ystep
	y_step = TILE_SIZE;
	if (!is_ray_facing_down(ray_angle)) // if ray is facing up
		y_step *= -1;
	
	x_step = TILE_SIZE / tan(ray_angle);
	if (!is_ray_facing_right(ray_angle) && x_step > 0)
		x_step *= -1;
	else if (is_ray_facing_right(ray_angle) && x_step < 0)
		x_step *= -1;
		
	next_horz_touch_x = x_intercept;
	next_horz_touch_y = y_intercept;
	if (!is_ray_facing_down(ray_angle))
		next_horz_touch_y --;
	while (next_horz_touch_x >= 0 && next_horz_touch_x <= WINDOW_WIDTH && next_horz_touch_y >= 0 && next_horz_touch_y <= WINDOW_HEIGHT)
	{
		if (is_wall(next_horz_touch_x, next_horz_touch_y))
		{
			// we hit the wall
			// found_horz_wall_hit = 1;
			*horz_wall_hit_x = next_horz_touch_x;
			*horz_wall_hit_y = next_horz_touch_y;
			return (1);
			// draw_line(mlx, mlx->player.player_x, mlx->player.player_y, horz_wall_hit_x, horz_wall_hit_y, 0xfff000);
			break ;
		}
		next_horz_touch_x += x_step;
		next_horz_touch_y += y_step;
	}
	return (0);
}

int	find_vertical_intersections(t_mlx_data *mlx, double *vert_wall_hit_x, double *vert_wall_hit_y, double ray_angle)
{
	double	x_intercept;
	double	y_intercept;
	double	x_step;
	double	y_step;
	double	next_vert_touch_x;
	double	next_vert_touch_y;

	x_intercept = floor(mlx->player.player_x / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_right(ray_angle))
		x_intercept += TILE_SIZE;
	// find the x-coordinate of the closest vertical grid intersection
	y_intercept = mlx->player.player_y + (x_intercept - mlx->player.player_x) * tan(ray_angle);
	
	// calculate the increment xstep and ystep (deltax, deltay)
	x_step = TILE_SIZE;
	if (!is_ray_facing_right(ray_angle)) // is ray facing left
	 	x_step *= -1;
	y_step = TILE_SIZE * tan(ray_angle);
	if (!is_ray_facing_down(ray_angle) && y_step > 0)
		y_step *= -1;
	else if (is_ray_facing_down(ray_angle) && y_step < 0)
		y_step *= -1;
	
	next_vert_touch_x = x_intercept;
	next_vert_touch_y = y_intercept;
	if (!is_ray_facing_right(ray_angle))
		next_vert_touch_x --;
	while (next_vert_touch_x >= 0 && next_vert_touch_x <= WINDOW_WIDTH && next_vert_touch_y >= 0 && next_vert_touch_y <= WINDOW_HEIGHT)
	{
		if (is_wall(next_vert_touch_x, next_vert_touch_y))
		{
			// found_vert_wall_hit = 1;
			*vert_wall_hit_x = next_vert_touch_x;
			*vert_wall_hit_y = next_vert_touch_y;
			return (1);
		}
		next_vert_touch_x += x_step;
		next_vert_touch_y += y_step;
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
	// ------------ find horizontal interception -------------
	found_horz_wall_hit = find_horizontal_intersection(mlx, &horz_wall_hit_x, &horz_wall_hit_y, ray_angle);

	// ------------ find vertical interception -------------
	found_vert_wall_hit = find_vertical_intersections(mlx, &vert_wall_hit_x, &vert_wall_hit_y, ray_angle);
	// calculate both horz and vert distances and choose the smallest value
	get_smallest_distance(mlx, i, found_horz_wall_hit, found_vert_wall_hit,
							horz_wall_hit_x, horz_wall_hit_y, vert_wall_hit_x,
							vert_wall_hit_y);
	// draw_line(mlx, mlx->player.player_x, mlx->player.player_y, wall_hit_x, wall_hit_y, 0xfff000);
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
