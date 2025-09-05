/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 11:40:59 by mait-all          #+#    #+#             */
/*   Updated: 2025/09/04 18:14:38 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static int	load_texture(t_mlx_data *mlx, char *path, int i)
{
	mlx->textures[i].img = mlx_xpm_file_to_image (mlx->mlx_ptr, path,
			&mlx->textures[i].width, &mlx->textures[i].height);
	if (!mlx->textures[i].img)
	{
		perror("failed to load a texture\n");
		return (0);
	}
	mlx->textures[i].addr = mlx_get_data_addr(mlx->textures[i].img,
			&mlx->textures[i].bpp, &mlx->textures[i].line_length,
			&mlx->textures[i].endian);
	if (!mlx->textures[i].addr)
	{
		perror("failed to get the addr of a texture\n");
		return (0);
	}
	return (1);
}

static int	load_all_textures(t_mlx_data *mlx)
{
	if (!load_texture(mlx, mlx->map.NO, 0))
		return (0);
	if (!load_texture(mlx, mlx->map.SO, 1))
		return (0);
	if (!load_texture(mlx, mlx->map.EA, 2))
		return (0);
	if (!load_texture(mlx, mlx->map.WE, 3))
		return (0);
	if (!load_texture(mlx, "./textures/resized-eagle.xpm", 4))
		return (0);
	return (1);
}

int	mouse_handle(int x, int y, t_mlx_data *mlx)
{
	int	win_middle;

	win_middle = mlx->window_width / 2;
	(void)y;

	if (x > win_middle)
	{
		mlx->player.rotation_Angle += 0.03;
	}
	if (x < win_middle)
	{
		mlx->player.rotation_Angle -= 0.03;
	}
	normalize_angle(mlx->player.rotation_Angle);
	mlx_mouse_move(mlx->mlx_ptr, mlx->mlx_window, mlx->window_width / 2, mlx->window_height / 2);
	return (0);
}

void	launch(t_mlx_data *mlx)
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		exit(custom_error("Error:\nFailed to init MLX!\n"));
	mlx->mlx_window = mlx_new_window(mlx->mlx_ptr,
			mlx->window_width, mlx->window_height, "cub3d");
	if (!mlx->mlx_window)
		exit(custom_error("Error:\nFailed to create window!\n"));
	if (!load_all_textures(mlx))
		exit(custom_error("Error:\nFailed to load textures!\n"));
	mlx_hook(mlx->mlx_window, 2, 1L << 0, key_pressed, mlx);
	mlx_hook(mlx->mlx_window, 3, 1L << 1, key_released, mlx);
	mlx_hook(mlx->mlx_window, 6, 1L << 6, mouse_handle, mlx);
	mlx_loop_hook(mlx->mlx_ptr, update, mlx);
	mlx_hook(mlx->mlx_window, 17, 0, ft_cleanup, mlx);
	mlx_loop(mlx->mlx_ptr);
}
