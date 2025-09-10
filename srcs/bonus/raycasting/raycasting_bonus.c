/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 10:54:38 by mait-all          #+#    #+#             */
/*   Updated: 2025/09/10 09:43:57 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

void	calculate_ray_intersection_steps(double *x_step, double *y_step,
											double ray_angle, char type)
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
	x_intercept = mlx->player.px
		+ (y_intercept - mlx->player.py) / tan(ray_angle);
	calculate_ray_intersection_steps(&x_step, &y_step, ray_angle, 'h');
	while (x_intercept >= 0 && x_intercept <= mlx->map.cols * TILE_SIZE
		&& y_intercept >= 0 && y_intercept <= mlx->map.rows * TILE_SIZE)
	{
		if (is_wall(mlx, x_intercept, normalize_y_axis(y_intercept, ray_angle)))
			return (set_horz_wall_hit(mlx, x_intercept, y_intercept));
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
	y_intercept = mlx->player.py
		+ (x_intercept - mlx->player.px) * tan(ray_angle);
	calculate_ray_intersection_steps(&x_step, &y_step, ray_angle, 'v');
	while (x_intercept >= 0 && x_intercept <= mlx->map.cols * TILE_SIZE
		&& y_intercept >= 0 && y_intercept <= mlx->map.rows * TILE_SIZE)
	{
		if (is_wall(mlx, normalize_x_axis(x_intercept, ray_angle), y_intercept))
			return (set_vert_wall_hit(mlx, x_intercept, y_intercept));
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

	reset(mlx, i);
	ray_angle = normalize_angle(mlx->rays[i].ray_angle);
	mlx->rays[i].ray_angle = ray_angle;
	found_horz_wall_hit = find_horizontal_intersection(mlx, ray_angle);
	found_vert_wall_hit = find_vertical_intersections(mlx, ray_angle);
	if (found_horz_wall_hit)
		horz_hit_distance = get_distance_between_points(mlx->player.px,
				mlx->player.py, mlx->horz_wall_hit_x,
				mlx->horz_wall_hit_y);
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
	int		i;
	double	r_angle;

	r_angle = mlx->player.rotation_angle - (FOV / 2);
	i = 0;
	while (i < NUM_RAYS)
	{
		mlx->rays[i].ray_angle = r_angle;
		cast(mlx, i);
		r_angle += (FOV / NUM_RAYS);
		i++;
	}
}
