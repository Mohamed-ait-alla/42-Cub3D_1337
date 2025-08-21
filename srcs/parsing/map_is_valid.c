/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_is_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 18:27:49 by mdahani           #+#    #+#             */
/*   Updated: 2025/08/21 19:00:13 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void flood_fill(t_map *map, int x, int y, int len_of_line, char player)
{
    if (x < 0 || x >= map->rows || y < 0 || y >= len_of_line)
        return;
    if (map->copy_map[x][y] != '0' && map->copy_map[x][y] != player)
		return ;
    map->copy_map[x][y] = 'V';
    flood_fill(map, x + 1, y, len_of_line, player);
    flood_fill(map, x - 1, y, len_of_line, player);
    flood_fill(map, x, y + 1, len_of_line, player);
    flood_fill(map, x, y - 1, len_of_line, player);
}

bool map_is_valid(t_map *map)
{
    int x, y;
    
    x = 0;
    while (map->copy_map[x])
    {
        y = 0;
        while (map->copy_map[x][y])
        {
            if (map->copy_map[x][y] == 'N' || map->copy_map[x][y] == 'S' || map->copy_map[x][y] == 'E' || map->copy_map[x][y] == 'W')
            {
                if (!flood_fill(map, x, y, ft_strlen(map->copy_map[x]), map->copy_map[x][y]))
                    return (false);
            }
            y++;
        }
        x++;
    }
    return (true);
}
