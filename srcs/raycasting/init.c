/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 10:02:39 by mait-all          #+#    #+#             */
/*   Updated: 2025/07/27 10:03:27 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

void	init_player(t_mlx_data *mlx)
{
	mlx->player.player_x = WINDOW_WIDTH / 2;  // col 4
	mlx->player.player_y = WINDOW_HEIGHT / 2; // row 3
	mlx->player.turn_dir = 0;
	mlx->player.walk_dir = 0;
	mlx->player.rotation_Angle = PI / 2;
	mlx->player.rotation_speed = 2 * (PI / 180);
	mlx->player.move_speed = 2;
}
