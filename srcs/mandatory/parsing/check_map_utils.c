/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:53:11 by mdahani           #+#    #+#             */
/*   Updated: 2025/09/10 22:23:00 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

bool	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] <= 32)
		i++;
	if (line[i])
		return (false);
	return (true);
}

bool	is_map(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] <= 32)
		i++;
	if (ft_strncmp(&line[i], "NO", 2) == 0 || ft_strncmp(&line[i], "SO", 2) == 0
		|| ft_strncmp(&line[i], "WE", 2) == 0 || ft_strncmp(&line[i], "EA",
			2) == 0 || ft_strncmp(&line[i], "F", 1) == 0 || ft_strncmp(&line[i],
			"C", 1) == 0)
		return (false);
	if (!line[i])
		return (false);
	return (true);
}

bool	this_line_is_map(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] <= 32)
		i++;
	if (ft_strncmp(&line[i], "NO", 2) == 0 || ft_strncmp(&line[i], "SO", 2) == 0
		|| ft_strncmp(&line[i], "WE", 2) == 0 || ft_strncmp(&line[i], "EA",
			2) == 0 || ft_strncmp(&line[i], "F", 1) == 0 || ft_strncmp(&line[i],
			"C", 1) == 0)
		return (false);
	return (true);
}

int	check_order_of_map(char *file, t_map *map)
{
	int		fd;
	int		line_before_map;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	line_before_map = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!map->copy_map[0] || !ft_strcmp(line, map->copy_map[0]))
			break ;
		if (!this_line_is_map(line))
			line_before_map++;
	}
	close(fd);
	return (line_before_map);
}
