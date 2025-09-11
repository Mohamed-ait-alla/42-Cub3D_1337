/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:07:56 by mait-all          #+#    #+#             */
/*   Updated: 2025/09/11 17:53:21 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	main(int ac, char **av)
{
	t_mlx_data	mlx;
	t_map		map;

	ft_bzero(&mlx, sizeof(t_mlx_data));
	if (ac != 2 || !check_file_name(av[1]))
		exit (custom_error(&mlx, "Error:\nNo such file or directory!\n"));
	ft_bzero(&map, sizeof(t_map));
	if (!check_map(av[1], &map))
		exit (custom_error(&mlx, "Error:\nInvalid map!\n"));
	init_player(&mlx, &map);
	launch(&mlx);
	return (0);
}
