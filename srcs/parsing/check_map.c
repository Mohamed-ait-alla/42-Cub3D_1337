/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:09:12 by mdahani           #+#    #+#             */
/*   Updated: 2025/08/18 16:56:07 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool get_path_directions(int fd, t_map *map)
{
    char	*line;
    int		i;

    while (1)
    {
        line = get_next_line(fd);
		if (!line)
			break ;
		i = 0;
        while (line[i])
        {
			if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] <= 32)
			{
				i+= 2;
				while (line[i] <= 32 && line[i])
					i++;
				map->NO = ft_substr(line, i, ft_strlen(line) - i);
			}
			else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] <= 32)
			{
				i+= 2;
				while (line[i] <= 32 && line[i])
					i++;
				map->SO = ft_substr(line, i, ft_strlen(line) - i);
			}
			else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] <= 32)
			{
				i+= 2;
				while (line[i] <= 32 && line[i])
					i++;
				map->WE = ft_substr(line, i, ft_strlen(line) - i);
			}
			else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] <= 32)
			{
				i+= 2;
				while (line[i] <= 32 && line[i])
					i++;
				map->EA = ft_substr(line, i, ft_strlen(line) - i);
			}
            i++;
        }
    }
	printf("NO: %s\n", map->NO);
	printf("SO: %s\n", map->SO);
	printf("WE: %s\n", map->WE);
	printf("EA: %s\n", map->EA);
	return (map->NO && map->SO && map->WE && map->EA);
}

static bool get_F_C(int fd, t_map *map)
{
	char	*line;
	int		i;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		i = 0;
		while (line[i])
		{
			if (line[i] == 'F' && line[i + 1] <= 32)
			{
				printf("dkhal\n");
				i++;
				while (line[i] <= 32 && line[i])
					i++;
				map->f_color = ft_substr(line, i, ft_strlen(line) - i);			
			}
			else if (line[i] == 'C' && line[i + 1] <= 32)
			{
				i++;
				while (line[i] <= 32 && line[i])
					i++;
				map->c_color = ft_substr(line, i, ft_strlen(line) - i);			
			}
			i++;
		}
	}
	printf("F: %s\n", map->f_color);
	printf("C: %s\n", map->c_color);
	return (map->f_color && map->c_color);
}
// static bool check_valid_character(int fd, t_map *map)
// {
    
// }


bool check_map(char *file, t_map *map)
{
    int fd;

    fd = open(file, O_RDONLY);
    if (!get_path_directions(fd, map))
	{
		close(fd);
		return (false);
	}
	fd = open(file, O_RDONLY);
    if (!get_F_C(fd, map))
	{
		close(fd);
		return (false);
	}
	return(true);
}
