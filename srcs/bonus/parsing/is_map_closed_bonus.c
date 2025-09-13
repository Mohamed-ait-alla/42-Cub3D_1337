/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_closed_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 09:27:52 by mdahani           #+#    #+#             */
/*   Updated: 2025/09/13 15:16:43 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

static bool	conditions_of_is_map_closed(int y, int x, t_map *map)
{
	int	rows;
	int	cols;

	rows = map->rows;
	cols = ft_strlen(map->copy_map[0]);
	if (y == 0 || y == rows - 1 || x == 0 || x == cols - 1)
		return (false);
	if (y > 0 && map->copy_map[y - 1][x] == 'O')
		return (false);
	if (y < rows - 1 && map->copy_map[y + 1][x] == 'O')
		return (false);
	if (x > 0 && map->copy_map[y][x - 1] == 'O')
		return (false);
	if (x < cols - 1 && map->copy_map[y][x + 1] == 'O')
		return (false);
	return (true);
}

bool	is_map_closed(t_map *map)
{
	char	c;

	int (rows), (cols), (y), (x);
	rows = map->rows;
	cols = ft_strlen(map->copy_map[0]);
	y = 0;
	while (y < rows)
	{
		x = 0;
		while (x < cols)
		{
			c = map->copy_map[y][x];
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
				|| c == 'D')
			{
				if (!conditions_of_is_map_closed(y, x, map))
					return (false);
			}
			x++;
		}
		y++;
	}
	return (true);
}
