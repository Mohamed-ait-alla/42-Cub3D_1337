/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 10:02:39 by mait-all          #+#    #+#             */
/*   Updated: 2025/08/30 15:08:08 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	get_n_map_cols(char *row)
{
	int	count;
	
	if (!row)
		return (0);
	count = 0;
	while (row[count])
	{
		count++;
	}
	return (count - 1);
}

static double get_rotation_agnle(char p_char)
{
	if (p_char == 'N')
		return (3 * M_PI / 2);
	else if (p_char == 'S')
		return (M_PI / 2);
	else if (p_char == 'E')
		return (0);
	else if (p_char == 'W')
		return (M_PI);
	return (0);
}

void	init_player(t_mlx_data *mlx)
{
	mlx->player.px = mlx->map.px_player * TILE_SIZE;
	mlx->player.py = mlx->map.py_player * TILE_SIZE;
	mlx->player.rotation_Angle = get_rotation_agnle(mlx->map.player);
	mlx->player.rotation_speed = 2 * (M_PI / 180);
	mlx->player.move_speed = 0.8;
	mlx->keys.key_a = 0;
	mlx->keys.key_d = 0;
	mlx->keys.key_w = 0;
	mlx->keys.key_s = 0;
	mlx->keys.key_left = 0;
	mlx->keys.key_right = 0;
	mlx->keys.key_escape = 0;
	mlx->map.cols = get_n_map_cols(mlx->map.map[0]);
}

int	load_texture(t_mlx_data *mlx, char *path, int i)
{
	mlx->textures[i].img = mlx_xpm_file_to_image (mlx->mlx_ptr, path, &mlx->textures[i].width, &mlx->textures[i].height);
	if (!mlx->textures[i].img)
	{
		perror("failed to load a texture\n");
		return (0);
	}
	mlx->textures[i].addr = mlx_get_data_addr(mlx->textures[i].img, &mlx->textures[i].bpp, &mlx->textures[i].line_length, &mlx->textures[i].endian);
	if (!mlx->textures[i].addr)
	{
		perror("failed to get the addr of a texture\n");
		return (0);
	}
	return (1);
}

int	load_all_textures(t_mlx_data *mlx)
{
	if (!load_texture(mlx, mlx->map.NO, 0))
		return (0);
	if (!load_texture(mlx, mlx->map.SO, 1))
		return (0);
	if (!load_texture(mlx, mlx->map.EA, 2))
		return (0);
	if (!load_texture(mlx, mlx->map.WE, 3))
		return (0);
	printf("textures loaded successfully!\n");
	return (1);
}
