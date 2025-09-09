/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_order_textures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:49:06 by mdahani           #+#    #+#             */
/*   Updated: 2025/08/28 16:53:20 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	check_order_textures(t_map *map)
{
	if (map->ORDER_NO && map->ORDER_SO && map->ORDER_WE && map->ORDER_EA)
		return (true);
	return (false);
}
