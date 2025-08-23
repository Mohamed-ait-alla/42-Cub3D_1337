/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:09:12 by mdahani           #+#    #+#             */
/*   Updated: 2025/08/23 10:39:40 by mdahani          ###   ########.fr       */
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
		map->NO = ft_substr(line, i, (ft_strlen(line) - i) - 1);
		map->num_NO++;
	}
	else if (ft_strncmp(&line[i], "SO", 2) == 0 && line[i + 2] <= 32 && line[i + 2] && line[i + 2] != '\n')
	{
		i += 2;
		while (line[i] && line[i] <= 32)
			i++;
		map->SO = ft_substr(line, i, (ft_strlen(line) - i) - 1);
		map->num_SO++;
	}
	else if (ft_strncmp(&line[i], "WE", 2) == 0 && line[i + 2] <= 32 && line[i + 2] && line[i + 2] != '\n')
	{
		i += 2;
		while (line[i] && line[i] <= 32)
			i++;
		map->WE = ft_substr(line, i, (ft_strlen(line) - i) - 1);
		map->num_WE++;
	}
	else if (ft_strncmp(&line[i], "EA", 2) == 0 && line[i + 2] <= 32 && line[i + 2] && line[i + 2] != '\n')
	{
		i += 2;
		while (line[i] && line[i] <= 32)
			i++;
		map->EA = ft_substr(line, i, (ft_strlen(line) - i) - 1);
		map->num_EA++;
	}
	else if (ft_strncmp(&line[i], "F", 1) == 0 && line[i + 1] <= 32 && line[i + 1] && line[i + 1] != '\n')
	{
		i += 1;
		while (line[i] && line[i] <= 32)
			i++;
		map->f_color = ft_substr(line, i, (ft_strlen(line) - i) - 1);
		map->num_f_color++;
	}
	else if (ft_strncmp(&line[i], "C", 1) == 0 && line[i + 1] <= 32 && line[i + 1] && line[i + 1] != '\n')
	{
		i += 1;
		while (line[i] && line[i] <= 32)
			i++;
		map->c_color = ft_substr(line, i, (ft_strlen(line) - i) - 1);
		map->num_c_color++;
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
		return (false);
	return (true);
}

static bool this_line_is_map(char *line)
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
		return (false);
	return (true);
}


static bool check_chars_of_map(char *line, t_map *map)
{
	int i = 0;
	while (line[i] && line[i] <= 32)
		i++;
	if (!line[i])
		return (true);
	else if (!is_map(line))
		return (true);
	else if (line[i] == '1' || line[i] == '0' || line[i] == 'N' ||
    		line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
	{
		int j = 0;
		while (line[j])
		{
			if (line[j] == '1' || line[j] == '0' || line[j] == 'N' ||
    		line[j] == 'S' || line[j] == 'E' || line[j] == 'W' ||
    		line[j] <= 32)
			{
				if (line[j] == 'N')
					map->_N++;
				else if (line[j] == 'S')
					map->_S++;
				else if (line[j] == 'E')
					map->_E++;
				else if (line[j] == 'W')
					map->_W++;
				j++;
			}
			else
				return (false);
		}
	}
	else
		return (false);
	return (true);
}

static bool is_empty_line(char *line)
{
    int i = 0;
	while (line[i] && line[i] <= 32)
		i++;
	if (line[i])
		return (false);
    return (true);
}



bool check_map(char *file, t_map *map)
{
	int fd, i, line_before_map;
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

	// check chars of map
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return false;
	while ((line = get_next_line(fd)))
	{
		if (!check_chars_of_map(line, map))
			return (false);
	}

	// copy the map
	map->copy_map = malloc(sizeof(char *) * (map->rows + 1));
	map->map = malloc(sizeof(char *) * (map->rows + 1));
	if (!map->copy_map || !map->map)
		return (false);
	i = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (false);
	bool map_started = false;
	bool map_ended = false;
	while ((line = get_next_line(fd)))
	{
    	if (is_map(line))
		{
			if (map_ended)
				return (false);
			map_started = true;
			map->copy_map[i] = ft_strdup(line);
			map->map[i] = ft_strdup(line);
			i++;
		}
		else if (is_empty_line(line))
		{
			if (map_started)
				map_ended = true;
		}
	}
	map->copy_map[i] = NULL;
	map->map[i] = NULL;


	// check order of mape
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (false);
	line_before_map = 0;
	while ((line = get_next_line(fd)))
	{
		if (!map->copy_map[0] || !ft_strcmp(line, map->copy_map[0]))
			break ;
		
		if (!this_line_is_map(line))
			line_before_map++;
	}
	
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
		printf("%s", map->copy_map[i]);
	}
	printf("\n");
	printf("line_before_map: %d\n", line_before_map);
	printf("N_N: %d\n", map->_N);
	printf("N_S: %d\n", map->_S);
	printf("N_E: %d\n", map->_E);
	printf("N_W: %d\n", map->_W);
	return (map->NO && map->SO && map->WE && map->EA &&
			map->f_color && map->c_color && map->rows &&
			map->num_NO == 1 && map->num_SO == 1 &&
			map->num_WE == 1 && map->num_EA == 1 &&
			map->num_f_color == 1 && map->num_c_color == 1 &&
			line_before_map == 6 && check_num_of_players(map) &&
			check_color(map) && map_is_valid(map));
}
