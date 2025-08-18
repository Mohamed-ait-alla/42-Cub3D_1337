/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 11:09:12 by mdahani           #+#    #+#             */
/*   Updated: 2025/08/18 11:19:04 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool check_valid_character(int fd, t_map *map)
{
    
}


bool check_map(char *file, t_map *map)
{
    int fd;

    fd = open(file, O_RDONLY);
    if (!check_valid_character(fd, map))
		return (0);
}