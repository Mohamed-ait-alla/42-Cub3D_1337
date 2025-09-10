/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 20:34:11 by mdahani           #+#    #+#             */
/*   Updated: 2025/09/10 22:29:16 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static bool	ini_alloc_map(t_map *map)
{
	map->copy_map = ft_malloc(sizeof(char *) * (map->rows + 1), 1);
	map->map = ft_malloc(sizeof(char *) * (map->rows + 1), 1);
	if (!map->copy_map || !map->map)
		return (false);
	return (true);
}

static void	finalize_map(t_map *map, int i)
{
	map->copy_map[i] = NULL;
	map->map[i] = NULL;
}

static bool	copy_map(t_map *map, int fd, bool *map_started, bool *map_ended)
{
	char*(line);
	int (i);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (is_map(line))
		{
			if ((*map_ended))
				return (false);
			(*map_started) = true;
			map->copy_map[i] = ft_strdup(line);
			map->map[i] = ft_strdup(line);
			i++;
		}
		else if (is_empty_line(line))
		{
			if ((*map_started))
				(*map_ended) = true;
		}
	}
	finalize_map(map, i);
	return (true);
}

bool	get_map(t_map *map, char *file)
{
	bool	map_started;
	bool	map_ended;
	int		fd;

	if (!ini_alloc_map(map))
		return (false);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (false);
	map_started = false;
	map_ended = false;
	if (!copy_map(map, fd, &map_started, &map_ended))
	{
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}
