/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_px_py_and_normalize_map_bonus.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 18:27:49 by mdahani           #+#    #+#             */
/*   Updated: 2025/09/13 15:18:35 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

static int	get_big_line(char **map)
{
	int (i), (big_line);
	big_line = 0;
	i = 0;
	while (map[i])
	{
		if (big_line < (int)ft_strlen(map[i]))
			big_line = ft_strlen(map[i]);
		i++;
	}
	return (big_line);
}

static void	normalize_the_map(char **map)
{
	int (x), (y), (big_line), (count_chars);
	big_line = get_big_line(map);
	x = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] <= 32)
				map[x][y] = 'O';
			y++;
		}
		if ((int)ft_strlen(map[x]) < big_line)
		{
			count_chars = big_line - (int)ft_strlen(map[x]);
			while (count_chars > 0)
			{
				map[x] = ft_strjoin(map[x], "O");
				count_chars--;
			}
		}
		x++;
	}
}

static void	get_position_of_doors(t_map *map, int x, int y, int *i)
{
	if (map->map[x][y] == 'D')
	{
		map->doors[(*i)].is_open = 0;
		map->doors[(*i)].x = y;
		map->doors[(*i)].y = x;
		(*i)++;
		map->doors_count++;
	}
}

void	get_px_py_and_normalize_map(t_map *map)
{
	int (x), (y), (i);
	normalize_the_map(map->copy_map);
	normalize_the_map(map->map);
	i = 0;
	x = 0;
	while (map->copy_map[x])
	{
		y = 0;
		while (map->copy_map[x][y])
		{
			if (map->copy_map[x][y] == 'N' || map->copy_map[x][y] == 'S'
				|| map->copy_map[x][y] == 'E' || map->copy_map[x][y] == 'W')
			{
				map->px_player = y;
				map->py_player = x;
				map->player = map->copy_map[x][y];
			}
			get_position_of_doors(map, x, y, &i);
			y++;
		}
		x++;
	}
}
