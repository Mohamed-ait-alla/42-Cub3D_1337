/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 10:06:57 by mait-all          #+#    #+#             */
/*   Updated: 2025/08/31 11:07:24 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int is_wall(t_mlx_data *mlx, double x, double y) {
    if (x < 0 || y < 0 || x >= mlx->map.cols * TILE_SIZE || y >= mlx->map.rows * TILE_SIZE)
	{
        return 1;	
	}
	// if (!is_ray_facing_down(mlx->ray_angle)) // if ray is facing up get the y inside the cell.
	// 	y--;		
	// if (!is_ray_facing_right(mlx->ray_angle)) // if ray is facing left get the x inside the cell.
	// 	x--;	
    int grid_x = x / TILE_SIZE;
    int grid_y = y / TILE_SIZE;
    return mlx->map.map[grid_y][grid_x] == '1';
}

int	key_pressed(int keycode, t_mlx_data *mlx)
{
	if (keycode == XK_Escape)
		mlx->keys.key_escape = 1;
	if (keycode == XK_Left)
		mlx->keys.key_left = 1;
	if (keycode == XK_Right)
		mlx->keys.key_right = 1;
	if (keycode == XK_a)
		mlx->keys.key_a = 1;
	if (keycode == XK_d)
		mlx->keys.key_d = 1;
	if (keycode == XK_w)
		mlx->keys.key_w = 1;
	if (keycode == XK_s)
		mlx->keys.key_s = 1;
	return (0);
}

int	key_released(int keycode, t_mlx_data *mlx)
{
	if (keycode == XK_Escape)
		mlx->keys.key_escape = 0;
	if (keycode == XK_Left)
		mlx->keys.key_left = 0;
	if (keycode == XK_Right)
		mlx->keys.key_right = 0;
	if (keycode == XK_a)
		mlx->keys.key_a = 0;
	if (keycode == XK_d)
		mlx->keys.key_d = 0;
	if (keycode == XK_w)
		mlx->keys.key_w = 0;
	if (keycode == XK_s)
		mlx->keys.key_s = 0;
	return (0);
}

int has_collision(t_mlx_data *mlx, float x, float y)
{
    float r = 0.5;

    if (is_wall(mlx, x - r, y - r)) return 1;
    if (is_wall(mlx, x + r, y - r)) return 1;
    if (is_wall(mlx, x - r, y + r)) return 1;
    if (is_wall(mlx, x + r, y + r)) return 1;
    return 0;
}


void	update_player_position(t_mlx_data *mlx)
{
	float	next_x;
	float	next_y;

	next_x = mlx->player.px;
	next_y = mlx->player.py;
	
	// handle escape: close the game
	if (mlx->keys.key_escape)
		ft_cleanup(mlx);
	// for moving the feild-of-view angle
	if (mlx->keys.key_right)
		mlx->player.rotation_Angle += 0.01;
	if (mlx->keys.key_left)
		mlx->player.rotation_Angle -= 0.01;
		
	// for moving the player: right, left, forward, backward
	if (mlx->keys.key_w)
	{
		next_x += cos(mlx->player.rotation_Angle) * mlx->player.move_speed;
		next_y += sin(mlx->player.rotation_Angle) * mlx->player.move_speed;
	}
	if (mlx->keys.key_s)
	{
		next_x -= cos(mlx->player.rotation_Angle) * mlx->player.move_speed;
		next_y -= sin(mlx->player.rotation_Angle) * mlx->player.move_speed;
	}
	if (mlx->keys.key_a)
	{
		next_x += sin(mlx->player.rotation_Angle) * mlx->player.move_speed;
		next_y -= cos(mlx->player.rotation_Angle) * mlx->player.move_speed;
	}
	if (mlx->keys.key_d)
	{
		next_x -= sin(mlx->player.rotation_Angle) * mlx->player.move_speed;
		next_y += cos(mlx->player.rotation_Angle) * mlx->player.move_speed;
	}

	// check for wall collision
	if (!has_collision(mlx, next_x, next_y))
	{
		mlx->player.px = next_x;
		mlx->player.py = next_y;
	}
	
}
