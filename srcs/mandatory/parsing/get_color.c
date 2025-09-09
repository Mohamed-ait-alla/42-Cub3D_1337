/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 10:29:40 by mdahani           #+#    #+#             */
/*   Updated: 2025/09/02 18:34:02 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static int	convert_rgb_to_int(int r, int g, int b)
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
