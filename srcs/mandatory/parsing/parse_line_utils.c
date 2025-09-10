/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 18:29:00 by mdahani           #+#    #+#             */
/*   Updated: 2025/09/10 18:45:59 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	parse_line_of_no(int *i, char *line, t_map *map)
{
	(*i) += 2;
	while (line[(*i)] && line[(*i)] <= 32)
		(*i)++;
	map->NO = ft_substr(line, (*i), (ft_strlen(line) - (*i)) - 1);
	if (!map->SO && !map->WE && !map->EA)
		map->ORDER_NO = true;
	map->num_NO++;
}

void	parse_line_of_so(int *i, char *line, t_map *map)
{
	(*i) += 2;
	while (line[(*i)] && line[(*i)] <= 32)
		(*i)++;
	map->SO = ft_substr(line, (*i), (ft_strlen(line) - (*i)) - 1);
	if (map->NO && !map->WE && !map->EA)
		map->ORDER_SO = true;
	map->num_SO++;
}

void	parse_line_of_we(int *i, char *line, t_map *map)
{
	(*i) += 2;
	while (line[(*i)] && line[(*i)] <= 32)
		(*i)++;
	map->WE = ft_substr(line, (*i), (ft_strlen(line) - (*i)) - 1);
	if (map->NO && map->SO && !map->EA)
		map->ORDER_WE = true;
	map->num_WE++;
}

void	parse_line_of_ea(int *i, char *line, t_map *map)
{
	(*i) += 2;
	while (line[(*i)] && line[(*i)] <= 32)
		(*i)++;
	map->EA = ft_substr(line, (*i), (ft_strlen(line) - (*i)) - 1);
	if (map->NO && map->SO && map->WE)
		map->ORDER_EA = true;
	map->num_EA++;
}
