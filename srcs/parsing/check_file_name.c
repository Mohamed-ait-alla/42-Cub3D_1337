/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_name.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 10:01:26 by mdahani           #+#    #+#             */
/*   Updated: 2025/08/18 10:20:48 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	check_file_name(char *file_name)
{
	size_t	len;

	len = ft_strlen(file_name);
	if (len > 4 && file_name[len - 4] == '.' && file_name[len - 3] == 'c'
		&& file_name[len - 2] == 'u' && file_name[len - 1] == 'b')
		return (true);
	return (false);
}
