/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:48:52 by mait-all          #+#    #+#             */
/*   Updated: 2025/09/01 18:53:03 by mait-all         ###   ########.fr       */
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

int	is_ray_facing_down(double ray_angle)
{
	return (ray_angle > 0 && ray_angle < M_PI);
}

int is_ray_facing_right(double ray_angle)
{
	return (ray_angle < 0.5 * M_PI || ray_angle > 1.5 * M_PI);
}

double normalize_x_axis(double x, double ray_angle)
{
	if (!is_ray_facing_right(ray_angle))
		return (--x);
	return (x);
}

double normalize_y_axis(double y, double ray_angle)
{
	if (!is_ray_facing_down(ray_angle))
		return (--y);
	return (y);
}
