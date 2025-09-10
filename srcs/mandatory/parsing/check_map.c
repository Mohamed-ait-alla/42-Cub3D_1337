/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:09:12 by mdahani           #+#    #+#             */
/*   Updated: 2025/09/10 22:50:39 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void	parse_line(char *line, t_map *map)
{
	int	i;

	i = 0;
	while (line[i] && line[i] <= 32)
		i++;
	if (ft_strncmp(&line[i], "NO", 2) == 0 && line[i + 2] <= 32 && line[i + 2]
		&& line[i + 2] != '\n')
		parse_line_of_no(&i, line, map);
	else if (ft_strncmp(&line[i], "SO", 2) == 0 && line[i + 2] <= 32
		&& line[i + 2] && line[i + 2] != '\n')
		parse_line_of_so(&i, line, map);
	else if (ft_strncmp(&line[i], "WE", 2) == 0 && line[i + 2] <= 32
		&& line[i + 2] && line[i + 2] != '\n')
		parse_line_of_we(&i, line, map);
	else if (ft_strncmp(&line[i], "EA", 2) == 0 && line[i + 2] <= 32
		&& line[i + 2] && line[i + 2] != '\n')
		parse_line_of_ea(&i, line, map);
	else if (ft_strncmp(&line[i], "F", 1) == 0 && line[i + 1] <= 32
		&& line[i + 1] && line[i + 1] != '\n')
		parse_line_of_f_color(&i, line, map);
	else if (ft_strncmp(&line[i], "C", 1) == 0 && line[i + 1] <= 32
		&& line[i + 1] && line[i + 1] != '\n')
		parse_line_of_c_color(&i, line, map);
}

static bool	check_chars_of_map(char *line, t_map *map)
{
	int	i;

	i = 0;
	while (line[i] && line[i] <= 32)
		i++;
	if (!line[i])
		return (true);
	else if (!is_map(line))
		return (true);
	else if (line[i] == '1' || line[i] == '0' || line[i] == 'N'
		|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
	{
		if (!check_chars_map_and_count_player(line, map))
			return (false);
	}
	else
		return (false);
	return (true);
}

static bool	parse_attributes_of_map(char *file, t_map *map)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (false);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		parse_line(line, map);
		if (is_map(line))
			map->rows++;
	}
	close(fd);
	return (true);
}

static bool	check_characters_of_map(char *file, t_map *map)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (false);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!check_chars_of_map(line, map))
		{
			close(fd);
			return (false);
		}
	}
	close(fd);
	return (true);
}

bool	check_map(char *file, t_map *map)
{
	if (!parse_attributes_of_map(file, map))
		return (false);
	if (!check_characters_of_map(file, map))
		return (false);
	if (!get_map(map, file))
		return (false);
	return (map->no && map->so && map->we && map->ea
		&& check_order_textures(map) && map->f_color && map->c_color
		&& map->rows && map->num_no == 1 && map->num_so == 1 && map->num_we == 1
		&& map->num_ea == 1 && map->num_f_color == 1 && map->num_c_color == 1
		&& check_order_of_map(file, map) == 6 && check_num_of_players(map)
		&& check_color(map) && map_is_valid(map));
}
