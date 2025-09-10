/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 18:29:00 by mdahani           #+#    #+#             */
/*   Updated: 2025/09/10 22:52:47 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	parse_line_of_no(int *i, char *line, t_map *map)
{
	(*i) += 2;
	while (line[(*i)] && line[(*i)] <= 32)
		(*i)++;
	map->no = ft_substr(line, (*i), (ft_strlen(line) - (*i)) - 1);
	if (!map->so && !map->we && !map->ea)
		map->order_no = true;
	map->num_no++;
}

void	parse_line_of_so(int *i, char *line, t_map *map)
{
	(*i) += 2;
	while (line[(*i)] && line[(*i)] <= 32)
		(*i)++;
	map->so = ft_substr(line, (*i), (ft_strlen(line) - (*i)) - 1);
	if (map->no && !map->we && !map->ea)
		map->order_so = true;
	map->num_so++;
}

void	parse_line_of_we(int *i, char *line, t_map *map)
{
	(*i) += 2;
	while (line[(*i)] && line[(*i)] <= 32)
		(*i)++;
	map->we = ft_substr(line, (*i), (ft_strlen(line) - (*i)) - 1);
	if (map->no && map->so && !map->ea)
		map->order_we = true;
	map->num_we++;
}

void	parse_line_of_ea(int *i, char *line, t_map *map)
{
	(*i) += 2;
	while (line[(*i)] && line[(*i)] <= 32)
		(*i)++;
	map->ea = ft_substr(line, (*i), (ft_strlen(line) - (*i)) - 1);
	if (map->no && map->so && map->we)
		map->order_ea = true;
	map->num_ea++;
}
