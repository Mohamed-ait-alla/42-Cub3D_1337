/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_is_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 18:27:49 by mdahani           #+#    #+#             */
/*   Updated: 2025/09/10 13:13:54 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

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

static void	normalize_the_map(t_map *map)
{
	int (x), (y), (big_line), (count_chars);
	big_line = get_big_line(map->copy_map);
	x = 0;
	while (map->copy_map[x])
	{
		y = 0;
		while (map->copy_map[x][y])
		{
			if (map->copy_map[x][y] <= 32)
				map->copy_map[x][y] = 'O';
			y++;
		}
		if ((int)ft_strlen(map->copy_map[x]) < big_line)
		{
			count_chars = big_line - (int)ft_strlen(map->copy_map[x]);
			while (count_chars > 0)
			{
				map->copy_map[x] = ft_strjoin(map->copy_map[x], "O");
				count_chars--;
			}
		}
		x++;
	}
}

static bool	flood_fill(t_map *map, int x, int y, char player)
{
	char	c;

	if (x < 0 || x >= map->rows || y < 0
		|| y >= (int)ft_strlen(map->copy_map[x]))
		return (false);
	c = map->copy_map[x][y];
	if (c == 'O')
		return (false);
	if (c != '0' && c != player)
		return (true);
	map->copy_map[x][y] = 'V';
	if (!flood_fill(map, x + 1, y, player))
		return (false);
	if (!flood_fill(map, x - 1, y, player))
		return (false);
	if (!flood_fill(map, x, y + 1, player))
		return (false);
	if (!flood_fill(map, x, y - 1, player))
		return (false);
	return (true);
}

bool	map_is_valid(t_map *map)
{
	int (x), (y);
	normalize_the_map(map);
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
				if (!flood_fill(map, x, y, map->copy_map[x][y]))
					return (false);
			}
			y++;
		}
		x++;
	}
	return (true);
}
