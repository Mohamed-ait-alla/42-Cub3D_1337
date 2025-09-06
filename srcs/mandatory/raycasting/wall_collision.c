/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_collision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:46:55 by mait-all          #+#    #+#             */
/*   Updated: 2025/09/06 10:54:51 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int	is_wall(t_mlx_data *mlx, double x, double y)
{
	int	grid_x;
	int	grid_y;

	if (x < 0 || y < 0 || x >= mlx->map.cols * TILE_SIZE || y >= mlx->map.rows * TILE_SIZE)
		return (1);
	grid_x = x / TILE_SIZE;
	grid_y = y / TILE_SIZE;
	return (mlx->map.map[grid_y][grid_x] == '1');
}

int	has_collision(t_mlx_data *mlx, float x, float y)
{
	float	r;

	r = 0.1;
	if (is_wall(mlx, x - r, y - r))
		return (1);
	if (is_wall(mlx, x + r, y - r))
		return (1);
	if (is_wall(mlx, x - r, y + r))
		return (1);
	if (is_wall(mlx, x + r, y + r))
		return (1);
	return (0);
}
