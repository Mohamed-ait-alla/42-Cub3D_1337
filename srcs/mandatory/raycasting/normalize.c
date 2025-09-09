/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:44:16 by mait-all          #+#    #+#             */
/*   Updated: 2025/09/02 18:32:50 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

double	normalize_angle(double angle)
{
	angle = fmod(angle, (2 * M_PI));
	if (angle < 0)
		angle += (2 * M_PI);
	return (angle);
}

double	normalize_x_axis(double x, double ray_angle)
{
	if (!is_ray_facing_right(ray_angle))
		return (--x);
	return (x);
}

double	normalize_y_axis(double y, double ray_angle)
{
	if (!is_ray_facing_down(ray_angle))
		return (--y);
	return (y);
}
