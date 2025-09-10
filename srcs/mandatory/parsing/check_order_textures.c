/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_order_textures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:49:06 by mdahani           #+#    #+#             */
/*   Updated: 2025/09/10 22:54:08 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

bool	check_order_textures(t_map *map)
{
	if (map->order_no && map->order_so && map->order_we && map->order_ea)
		return (true);
	return (false);
}
