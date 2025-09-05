/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_is_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 18:27:49 by mdahani           #+#    #+#             */
/*   Updated: 2025/09/05 09:17:54 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void normalize_the_map(t_map *map)
{
    int x, y, big_line;
    
    // get the big line
    x = 0;
    big_line = 0;
    while (map->copy_map[x])
    {
        if (big_line < (int) ft_strlen(map->copy_map[x]))
            big_line = ft_strlen(map->copy_map[x]);
        x++;
    }
    // fill the white spaces on O
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
       if ((int) ft_strlen(map->copy_map[x]) < big_line)
        {
            int count_chars = big_line - (int) ft_strlen(map->copy_map[x]);
            while (count_chars > 0)
            {
                map->copy_map[x] = ft_strjoin(map->copy_map[x], "O");
                count_chars--;
            }
        }
        x++;
    }
}


static bool flood_fill(t_map *map, int x, int y, char player)
{
    if (x < 0 || x >= map->rows || y < 0 || y >= (int)ft_strlen(map->copy_map[x]))
        return (false);
    char c = map->copy_map[x][y];
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

bool map_is_valid(t_map *map)
{
    int x, y;
	int	i;

    // normalize the map
    normalize_the_map(map);
    x = 0;
	i = 0;
    while (map->copy_map[x])
    {
        y = 0;
        while (map->copy_map[x][y])
        {
            if (map->copy_map[x][y] == 'N' || map->copy_map[x][y] == 'S' || map->copy_map[x][y] == 'E' || map->copy_map[x][y] == 'W')
            {
                map->px_player = y;
                map->py_player = x;
                map->player = map->copy_map[x][y];
                if (!flood_fill(map, x, y, map->copy_map[x][y]))
                    return (false);                
            }
			if (map->copy_map[x][y] == 'D')
			{
				map->doors[i].is_open = 0;
				map->doors[i].x = y;
				map->doors[i].y = x;
				i++;
				map->doors_count ++;
			}
            y++;
        }
        x++;
    }

    printf("map after flood fill\n");
    for (int i = 0; map->copy_map[i]; i++)
    {
        printf("%s\n", map->copy_map[i]);
    }
    printf("\n");
    printf("px_player: %f\n", map->px_player);
    printf("py_player: %f\n", map->py_player);
    printf("char of player: %c\n", map->player);
    return (true);
}
