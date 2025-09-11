/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_utils_plus_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 18:43:00 by mdahani           #+#    #+#             */
/*   Updated: 2025/09/11 11:46:04 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

void	parse_line_of_f_color(int *i, char *line, t_map *map)
{
	(*i) += 1;
	while (line[(*i)] && line[(*i)] <= 32)
		(*i)++;
	map->f_color = ft_substr(line, (*i), (ft_strlen(line) - (*i)) - 1);
	map->num_f_color++;
}

void	parse_line_of_c_color(int *i, char *line, t_map *map)
{
	(*i) += 1;
	while (line[(*i)] && line[(*i)] <= 32)
		(*i)++;
	map->c_color = ft_substr(line, (*i), (ft_strlen(line) - (*i)) - 1);
	map->num_c_color++;
}

bool	check_chars_map_and_count_player(char *line, t_map *map)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '1' || line[i] == '0' || line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W' || line[i] == 'D'
			|| line[i] <= 32)
		{
			if (line[i] == 'N')
				map->player_n++;
			else if (line[i] == 'S')
				map->player_s++;
			else if (line[i] == 'E')
				map->player_e++;
			else if (line[i] == 'W')
				map->player_w++;
			else if (line[i] == 'D')
				map->char_door++;
			i++;
		}
		else
			return (false);
	}
	return (true);
}
