/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_order_textures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:49:06 by mdahani           #+#    #+#             */
/*   Updated: 2025/09/02 18:34:00 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

bool	check_order_textures(t_map *map)
{
	if (map->ORDER_NO && map->ORDER_SO && map->ORDER_WE && map->ORDER_EA)
		return (true);
	return (false);
}
