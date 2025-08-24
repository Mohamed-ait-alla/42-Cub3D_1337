/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_num_of_players.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 15:43:13 by mdahani           #+#    #+#             */
/*   Updated: 2025/08/21 15:45:29 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool check_num_of_players(t_map *map)
{
    if ((map->_N + map->_S +map->_E + map->_W) != 1)
        return (false);
    return (true);
}
