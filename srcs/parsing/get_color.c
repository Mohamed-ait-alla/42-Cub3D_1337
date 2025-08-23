/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 10:29:40 by mdahani           #+#    #+#             */
/*   Updated: 2025/08/23 10:46:00 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	convert_rgb_to_int(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
}

void	get_color(t_map *map)
{
	char **f_color, **c_color;

	f_color = ft_split(map->f_color, ',');
	c_color = ft_split(map->c_color, ',');

	map->floor_color = convert_rgb_to_int(ft_atoi(f_color[0]),
            ft_atoi(f_color[1]),ft_atoi(f_color[2]));
	map->ceiling_color = convert_rgb_to_int(ft_atoi(c_color[0]),
            ft_atoi(c_color[1]),ft_atoi(c_color[2]));
}
