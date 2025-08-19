/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:09:12 by mdahani           #+#    #+#             */
/*   Updated: 2025/08/19 15:43:38 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void parse_line(char *line, t_map *map)
{
	int i = 0;

	while (line[i] && line[i] <= 32)
		i++;

	if (ft_strncmp(&line[i], "NO", 2) == 0 && line[i + 2] <= 32 && line[i + 2] && line[i + 2] != '\n')
	{
		i += 2;
		while (line[i] && line[i] <= 32)
			i++;
		map->NO = ft_substr(line, i, ft_strlen(line) - i);
	}
	else if (ft_strncmp(&line[i], "SO", 2) == 0 && line[i + 2] <= 32 && line[i + 2] && line[i + 2] != '\n')
	{
		i += 2;
		while (line[i] && line[i] <= 32)
			i++;
		map->SO = ft_substr(line, i, ft_strlen(line) - i);
	}
	else if (ft_strncmp(&line[i], "WE", 2) == 0 && line[i + 2] <= 32 && line[i + 2] && line[i + 2] != '\n')
	{
		i += 2;
		while (line[i] && line[i] <= 32)
			i++;
		map->WE = ft_substr(line, i, ft_strlen(line) - i);
	}
	else if (ft_strncmp(&line[i], "EA", 2) == 0 && line[i + 2] <= 32 && line[i + 2] && line[i + 2] != '\n')
	{
		i += 2;
		while (line[i] && line[i] <= 32)
			i++;
		map->EA = ft_substr(line, i, ft_strlen(line) - i);
	}
	else if (ft_strncmp(&line[i], "F", 1) == 0 && line[i + 1] <= 32 && line[i + 1] && line[i + 1] != '\n')
	{
		i += 1;
		while (line[i] && line[i] <= 32)
			i++;
		map->f_color = ft_substr(line, i, ft_strlen(line) - i);
	}
	else if (ft_strncmp(&line[i], "C", 1) == 0 && line[i + 1] <= 32 && line[i + 1] && line[i + 1] != '\n')
	{
		i += 1;
		while (line[i] && line[i] <= 32)
			i++;
		map->c_color = ft_substr(line, i, ft_strlen(line) - i);
	}
}
static bool is_map(char *line)
{
	int i = 0;
	while (line[i] && line[i] <= 32)
		i++;
	if (ft_strncmp(&line[i], "NO", 2) == 0 ||
		ft_strncmp(&line[i], "SO", 2) == 0 ||
		ft_strncmp(&line[i], "WE", 2) == 0 ||
		ft_strncmp(&line[i], "EA", 2) == 0 ||
		ft_strncmp(&line[i], "F", 1) == 0 ||
		ft_strncmp(&line[i], "C", 1) == 0)
		return false;
	if (!line[i])
		return false;
	return true;
}

bool check_map(char *file, t_map *map)
{
	int fd, i;
	char *line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return false;
	
	while ((line = get_next_line(fd)))
	{
		parse_line(line, map);
		if (is_map(line))
			map->rows++;
	}
	// copy the map
	map->copy_map = malloc(sizeof(char *) * (map->rows + 1));
	if (!map->copy_map)
		return (false);
	i = 0;
	fd = open(file, O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		if (is_map(line))
			map->copy_map[i++] = ft_strdup(line);
	}
	map->copy_map[i] = NULL;
	close(fd);
	printf("NO: %s\n", map->NO);
	printf("SO: %s\n", map->SO);
	printf("WE: %s\n", map->WE);
	printf("EA: %s\n", map->EA);
	printf("F: %s\n", map->f_color);
	printf("C: %s\n", map->c_color);

	printf("rows of map: %d\n", map->rows);
	printf("copy map:\n");
	for (int i = 0; map->copy_map[i]; i++)
	{
		printf("%s\n", map->copy_map[i]);
	}
	return (map->NO && map->SO && map->WE && map->EA &&
			map->f_color && map->c_color && map->rows);
}
