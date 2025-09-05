/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_collision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:46:55 by mait-all          #+#    #+#             */
/*   Updated: 2025/09/04 16:17:03 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int	is_wall(t_mlx_data *mlx, double x, double y)
{
	int	grid_x;
	int	grid_y;

	if (x < 0 || y < 0 || x > mlx->window_width || y > mlx->window_height)
		return (1);
	grid_x = x / TILE_SIZE;
	grid_y = y / TILE_SIZE;
	mlx->tile = mlx->map.map[grid_y][grid_x];
	return ((mlx->map.map[grid_y][grid_x] == '1') || mlx->map.map[grid_y][grid_x] == 'D');
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
// your approach doesn't work, but i found something interesting when i try to debug, especially in vertical intersection, i tried the set the player in map to E, so rays will only face vertical, why vertical because i try to print something on horz function and nothing is printed, then i try to print i actually the while inside the vertical intersection function stops or not and i find that it stops, but the problem is when i try to print which character that makes top and i found is 0, wich is not logic, because in my is_wall function returns only true if the grid is 1 or D, so i think this the issue why the vertical side doesn't rendred whith textures because this check will never be true if the grid is 0:

// 			if (mlx->tile == '1')
// 			{
// 				printf("vert:yes\n");
// 				mlx->vert_wall_hit_x = x_intercept;
// 				mlx->vert_wall_hit_y = y_intercept;
// 				mlx->vert_hit_door = 0;
// 				return (1);
// 			}
// 			if (mlx->tile == 'D')
// 			{
// 				mlx->vert_wall_hit_x = x_intercept;
// 				mlx->vert_wall_hit_y = y_intercept;
// 				mlx->vert_hit_door = 1;
// 				return (1);
// 			}

// this is also my is_wall function:

// int	is_wall(t_mlx_data *mlx, double x, double y) { 	int	grid_x; 	int	grid_y;  	if (x < 0 || y < 0 || x >= mlx->window_width || y >= mlx->window_height) 		return (1); 	grid_x = x / TILE_SIZE; 	grid_y = y / TILE_SIZE; 	mlx->tile = mlx->map.map[grid_y][grid_x]; 	return (mlx->map.map[grid_y][grid_x] == '1' || mlx->map.map[grid_y][grid_x] == 'D'); }