/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:08:59 by mdahani           #+#    #+#             */
/*   Updated: 2025/09/10 18:14:29 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static int	check_number_of_commas(char *color)
{
	int	i;
	int	number_of_commas;

	number_of_commas = 0;
	i = 0;
	while (color[i])
	{
		if (color[i] == ',')
			number_of_commas++;
		i++;
	}
	if (number_of_commas != 2)
		return (false);
	return (true);
}

static int	check_number_of_colors(char **color)
{
	int	color_count;
	int	i;
	int	j;

	color_count = 0;
	i = 0;
	while (color[i])
	{
		if (ft_atoi(color[i]) < 0 || ft_atoi(color[i]) > 255)
			return (0);
		j = 0;
		while (color[i][j])
		{
			if (!ft_isdigit(color[i][j]))
				return (0);
			j++;
		}
		i++;
		color_count++;
	}
	return (color_count);
}

bool	check_color(t_map *map)
{
	char	**f_color;
	char	**c_color;

	int (f_count), (c_count);
	f_count = 0;
	c_count = 0;
	if (!check_number_of_commas(map->f_color)
		|| !check_number_of_commas(map->c_color))
		return (false);
	f_color = ft_split(map->f_color, ',');
	c_color = ft_split(map->c_color, ',');
	f_count = check_number_of_colors(f_color);
	c_count = check_number_of_colors(c_color);
	if (f_count != 3 || c_count != 3)
		return (false);
	get_color(map);
	return (true);
}
