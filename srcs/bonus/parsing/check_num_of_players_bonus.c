/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_num_of_players_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 15:43:13 by mdahani           #+#    #+#             */
/*   Updated: 2025/09/11 11:51:59 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

bool	check_num_of_players(t_map *map)
{
	if ((map->player_n + map->player_s + map->player_e + map->player_w) != 1)
		return (false);
	return (true);
}
