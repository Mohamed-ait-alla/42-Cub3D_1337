/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 10:02:39 by mait-all          #+#    #+#             */
/*   Updated: 2025/09/11 21:07:20 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

static int	get_col_num(char *row)
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

int	calculate_map_cols(char **map)
{
	int	len;
	int	tmp;
	int	i;

	len = get_col_num(map[0]);
	i = 1;
	while (map[i])
	{
		tmp = get_col_num(map[i]);
		if (tmp > len)
			len = tmp;
		i++;
	}
	return (len);
}

static double	get_rotation_agnle(char p_char)
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

void	init_player(t_mlx_data *mlx, t_map *map)
{
	mlx->map = *map;
	mlx->player.anim_index = 5;
	mlx->player.px = (mlx->map.px_player * TILE_SIZE) + (TILE_SIZE / 2);
	mlx->player.py = (mlx->map.py_player * TILE_SIZE) + (TILE_SIZE / 2);
	mlx->player.rotation_angle = get_rotation_agnle(mlx->map.player);
	mlx->player.move_speed = 0.6;
	mlx->keys.key_a = 0;
	mlx->keys.key_d = 0;
	mlx->keys.key_w = 0;
	mlx->keys.key_s = 0;
	mlx->keys.key_left = 0;
	mlx->keys.key_right = 0;
	mlx->keys.key_esc = 0;
	mlx->keys.key_space = 0;
	mlx->map.cols = calculate_map_cols(mlx->map.map);
}
