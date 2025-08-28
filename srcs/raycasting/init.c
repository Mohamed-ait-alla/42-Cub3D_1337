/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 10:02:39 by mait-all          #+#    #+#             */
/*   Updated: 2025/08/28 11:31:51 by mait-all         ###   ########.fr       */
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

void	init_player(t_mlx_data *mlx)
{
	mlx->player.player_x = WINDOW_WIDTH / 2;
	mlx->player.player_y = WINDOW_HEIGHT / 2;
	mlx->player.rotation_Angle = PI / 2;
	mlx->player.rotation_speed = 2 * (PI / 180);
	mlx->player.move_speed = 1;
	mlx->keys.key_a = 0;
	mlx->keys.key_d = 0;
	mlx->keys.key_w = 0;
	mlx->keys.key_s = 0;
	mlx->keys.key_left = 0;
	mlx->keys.key_right = 0;
	mlx->keys.key_escape = 0;
	mlx->map.cols = get_n_map_cols(mlx->map.map[0]);
}

int	load_wall_texture(t_mlx_data *mlx, char *path)
{
	mlx->wall_texture.img = mlx_xpm_file_to_image (mlx->mlx_ptr, path, &mlx->wall_texture.width, &mlx->wall_texture.height);
	if (!mlx->wall_texture.img)
		printf("failed to load the wall texture\n");
	mlx->wall_texture.addr = mlx_get_data_addr(mlx->wall_texture.img, &mlx->wall_texture.bpp, &mlx->wall_texture.line_length, &mlx->wall_texture.endian);
	if (!mlx->wall_texture.addr)
		printf("failed to get the addr of the texture\n");
	printf("texture loaded successfully\n");
	return (1);
}
