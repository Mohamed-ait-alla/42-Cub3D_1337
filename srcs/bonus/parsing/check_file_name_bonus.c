/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_name_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 10:01:26 by mdahani           #+#    #+#             */
/*   Updated: 2025/09/06 11:17:40 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

bool	check_file_name(char *file_name)
{
	size_t	len;

	len = ft_strlen(file_name);
	if (len > 4 && file_name[len - 4] == '.' && file_name[len - 3] == 'c'
		&& file_name[len - 2] == 'u' && file_name[len - 1] == 'b')
		return (true);
	return (false);
}
