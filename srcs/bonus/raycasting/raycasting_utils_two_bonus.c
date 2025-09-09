/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils_two_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 13:14:06 by mait-all          #+#    #+#             */
/*   Updated: 2025/09/06 13:16:21 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

int	set_horz_wall_hit(t_mlx_data *mlx, double x_intercept, double y_intercept)
{
	if (mlx->tile == '1')
	{
		mlx->horz_wall_hit_x = x_intercept;
		mlx->horz_wall_hit_y = y_intercept;
		mlx->horz_hit_door = 0;
		return (1);
	}
	if (mlx->tile == 'D')
	{
		mlx->horz_wall_hit_x = x_intercept;
		mlx->horz_wall_hit_y = y_intercept;
		mlx->horz_hit_door = 1;
		return (1);
	}
	return (0);
}

int	set_vert_wall_hit(t_mlx_data *mlx, double x_intercept, double y_intercept)
{
	if (mlx->tile == '1')
	{
		mlx->vert_wall_hit_x = x_intercept;
		mlx->vert_wall_hit_y = y_intercept;
		mlx->vert_hit_door = 0;
		return (1);
	}
	if (mlx->tile == 'D')
	{
		mlx->vert_wall_hit_x = x_intercept;
		mlx->vert_wall_hit_y = y_intercept;
		mlx->vert_hit_door = 1;
		return (1);
	}
	return (0);
}

void	reset(t_mlx_data *mlx, int i)
{
	mlx->rays[i].was_hit_horz = 0;
	mlx->rays[i].was_hit_vert = 0;
	mlx->rays[i].was_hit_door = 0;
	mlx->vert_hit_door = 0;
	mlx->horz_hit_door = 0;
}
