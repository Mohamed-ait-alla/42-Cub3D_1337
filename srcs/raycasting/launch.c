/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 11:40:59 by mait-all          #+#    #+#             */
/*   Updated: 2025/09/01 15:40:38 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void launch(t_mlx_data *mlx)
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		exit(custom_error("Error:\nFailed to init MLX!\n"));
	mlx->mlx_window = mlx_new_window(mlx->mlx_ptr, mlx->window_width, mlx->window_height, "cub3d");
	if (!mlx->mlx_window)
		exit(custom_error("Error:\nFailed to create window!\n"));
	if (!load_all_textures(mlx))
		exit(custom_error("Error:\nFailed to load textures!\n"));
	mlx_hook(mlx->mlx_window, 2, 1L << 0, key_pressed, mlx);
	mlx_hook(mlx->mlx_window, 3, 1L << 1, key_released, mlx);
	mlx_loop_hook(mlx->mlx_ptr, update, mlx);
	mlx_hook(mlx->mlx_window, 17, 0, ft_cleanup, mlx);
	mlx_loop(mlx->mlx_ptr);
}
