/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 10:54:38 by mait-all          #+#    #+#             */
/*   Updated: 2025/07/28 20:24:50 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

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

void	cast(t_mlx_data *mlx, double ray_angle, int i)
{
	double	wall_hit_x;
	double	wall_hit_y;
	double	horz_wall_hit_x;
	double	horz_wall_hit_y;
	double	vert_wall_hit_x;
	double	vert_wall_hit_y;
	double	distance;
	double	x_intercept;
	double	y_intercept;
	double	x_step;
	double	y_step;
	int		is_ray_facing_down;
	int		is_ray_facing_up;
	int		is_ray_facing_right;
	int		is_ray_facing_left;
	double	next_horz_touch_x;
	double	next_horz_touch_y;
	double	next_vert_touch_x;
	double	next_vert_touch_y;
	double	found_horz_wall_hit = 0;
	double	found_vert_wall_hit = 0;
	double	horz_hit_distance;
	double	vert_hit_distance;
	
	horz_wall_hit_x = 0;
	horz_wall_hit_y = 0;
	vert_wall_hit_x = 0;
	vert_wall_hit_y = 0;
	distance = 0;
	ray_angle = normalize_angle(ray_angle);
	// get the ray facing angle
	is_ray_facing_down = ray_angle > 0 && ray_angle < PI;
	is_ray_facing_up = !is_ray_facing_down;
	is_ray_facing_right = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
	is_ray_facing_left = !is_ray_facing_right;
	// ------------ find horizontal interception -------------
	// find the y-coordinate of the closest horizontal grid intersection
	y_intercept = floor(mlx->player.player_y / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_down)
		y_intercept += TILE_SIZE;
	// find the x-coordinate of the closest horizontal grid intersection
	x_intercept = mlx->player.player_x + (y_intercept - mlx->player.player_y) / tan(ray_angle);
	
	// caluculate the increment of the closest horizontal xstep and ystep
	y_step = TILE_SIZE;
	if (is_ray_facing_up)
		y_step *= -1;
	
	x_step = TILE_SIZE / tan(ray_angle);
	if (is_ray_facing_left && x_step > 0)
		x_step *= -1;
	else if (is_ray_facing_right && x_step < 0)
		x_step *= -1;
		
	next_horz_touch_x = x_intercept;
	next_horz_touch_y = y_intercept;
	if (is_ray_facing_up)
		next_horz_touch_y --;
	while (next_horz_touch_x >= 0 && next_horz_touch_x <= WINDOW_WIDTH && next_horz_touch_y >= 0 && next_horz_touch_y <= WINDOW_HEIGHT)
	{
		if (is_wall(next_horz_touch_x, next_horz_touch_y))
		{
			// we hit the wall
			found_horz_wall_hit = 1;
			horz_wall_hit_x = next_horz_touch_x;
			horz_wall_hit_y = next_horz_touch_y;
			// draw_line(mlx, mlx->player.player_x, mlx->player.player_y, horz_wall_hit_x, horz_wall_hit_y, 0xfff000);
			break ;
		}
		next_horz_touch_x += x_step;
		next_horz_touch_y += y_step;
	}
	
	// ------------ find vertical interception -------------
	// find the x-coordinate of the closest vertical grid intersection
	x_intercept = floor(mlx->player.player_x / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_right)
		x_intercept += TILE_SIZE;
	// find the x-coordinate of the closest vertical grid intersection
	y_intercept = mlx->player.player_y + (x_intercept - mlx->player.player_x) * tan(ray_angle);
	
	// calculate the increment xstep and ystep (deltax, deltay)
	x_step = TILE_SIZE;
	if (is_ray_facing_left)
	 	x_step *= -1;
	y_step = TILE_SIZE * tan(ray_angle);
	if (is_ray_facing_up && y_step > 0)
		y_step *= -1;
	else if (is_ray_facing_down && y_step < 0)
		y_step *= -1;
	
	next_vert_touch_x = x_intercept;
	next_vert_touch_y = y_intercept;
	if (is_ray_facing_left)
		next_vert_touch_x --;
	while (next_vert_touch_x >= 0 && next_vert_touch_x <= WINDOW_WIDTH && next_vert_touch_y >= 0 && next_vert_touch_y <= WINDOW_HEIGHT)
	{
		if (is_wall(next_vert_touch_x, next_vert_touch_y))
		{
			found_vert_wall_hit = 1;
			vert_wall_hit_x = next_vert_touch_x;
			vert_wall_hit_y = next_vert_touch_y;
			break;
		}
		next_vert_touch_x += x_step;
		next_vert_touch_y += y_step;
	}
	
	// calculate both horz and vert distances and choose the smallest value
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
		wall_hit_x = horz_wall_hit_x;
	else
		wall_hit_x = vert_wall_hit_x;
	if (horz_hit_distance < vert_hit_distance)
		wall_hit_y = horz_wall_hit_y;
	else
		wall_hit_y = vert_wall_hit_y;
	if (horz_hit_distance < vert_hit_distance)
		mlx->rays[i].ray_distance = horz_hit_distance;
	else
		mlx->rays[i].ray_distance = vert_hit_distance;
	// draw_line(mlx, mlx->player.player_x, mlx->player.player_y, wall_hit_x, wall_hit_y, 0xfff000);
}

void	cast_rays(t_mlx_data *mlx)
{
	int	i = 0;

	double ray_angle = mlx->player.rotation_Angle - (FOV / 2);
	while (i < NUM_RAYS)
	{
		cast(mlx, ray_angle, i);
		// draw_line(mlx, mlx->player.player_x, mlx->player.player_y, mlx->player.player_x + cos(ray_angle) * 32, mlx->player.player_y + sin(ray_angle) * 32, 0x00ff00);
		i++;
		ray_angle += FOV / (NUM_RAYS);
	}
}
