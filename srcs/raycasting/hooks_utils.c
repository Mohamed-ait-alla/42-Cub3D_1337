/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 10:06:57 by mait-all          #+#    #+#             */
/*   Updated: 2025/07/27 10:08:03 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

int is_wall(float x, float y) {
	char	map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
		{'1', '1', '1', '1', '1', '1', '1', '1'},
		{'1', '0', '0', '0', '1', '0', '0', '1'},
		{'1', '1', '1', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '1', '1', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '1', '1', '1', '1', '1', '1', '1'},
	};
    if (x < 0 || y < 0 || x >= MAP_NUM_COLS * TILE_SIZE || y >= MAP_NUM_ROWS * TILE_SIZE)
        return 1;
    int grid_x = x / TILE_SIZE;
    int grid_y = y / TILE_SIZE;
    return map[grid_y][grid_x] == '1';
}

int	key_Pressed(int keycode, t_mlx_data *mlx)
{
	if (keycode == XK_Escape)
		ft_destroy_window(mlx);
	else if (keycode == XK_Left)
		mlx->player.rotation_Angle -= 0.1;
	else if (keycode == XK_Right)
		mlx->player.rotation_Angle += 0.1;
    else {
        float next_x = mlx->player.player_x;
        float next_y = mlx->player.player_y;

        if (keycode == XK_w) {
            next_x += cos(mlx->player.rotation_Angle) * mlx->player.move_speed;
            next_y += sin(mlx->player.rotation_Angle) * mlx->player.move_speed;
			if (!is_wall(next_x, next_y))
			{
				mlx->player.player_x = next_x;
				mlx->player.player_y = next_y;
			}
        } else if (keycode == XK_s) {
            next_x -= cos(mlx->player.rotation_Angle) * mlx->player.move_speed;
            next_y -= sin(mlx->player.rotation_Angle) * mlx->player.move_speed;
			if (!is_wall(next_x, next_y))
			{
				mlx->player.player_x = next_x;
				mlx->player.player_y = next_y;
			}
        }
		else if (keycode == XK_a)
		{
            next_x -= sin(mlx->player.rotation_Angle) * mlx->player.move_speed;
            next_y += cos(mlx->player.rotation_Angle) * mlx->player.move_speed;
			if (!is_wall(next_x, next_y))
			{
				mlx->player.player_x = next_x;
				mlx->player.player_y = next_y;
			}			
		}
		else if (keycode == XK_d)
		{
            next_x += sin(mlx->player.rotation_Angle) * mlx->player.move_speed;
            next_y -= cos(mlx->player.rotation_Angle) * mlx->player.move_speed;
			if (!is_wall(next_x, next_y))
			{
				mlx->player.player_x = next_x;
				mlx->player.player_y = next_y;
			}			
		}
    }
	return (0);
}