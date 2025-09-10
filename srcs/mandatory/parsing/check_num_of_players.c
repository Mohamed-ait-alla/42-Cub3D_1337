/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_num_of_players.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 15:43:13 by mdahani           #+#    #+#             */
/*   Updated: 2025/09/10 22:53:31 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

bool	check_num_of_players(t_map *map)
{
	if ((map->player_n + map->player_s + map->player_e + map->player_w) != 1)
		return (false);
	return (true);
}
