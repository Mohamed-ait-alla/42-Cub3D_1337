/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:07:56 by mait-all          #+#    #+#             */
/*   Updated: 2025/09/05 09:15:59 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_mlx_data	mlx;
	t_map		map;

	if (ac != 2 || !check_file_name(av[1]))
		exit (custom_error("Error:\nNo such file or directory!\n"));
	ft_bzero(&map, sizeof(t_map));
	if (!check_map(av[1], &map))
		exit (custom_error("Error:\nInvalid map!\n"));
	ft_bzero(&mlx, sizeof(t_mlx_data));
	init_player(&mlx, &map);
	printf("number of doors: %d\n", mlx.map.doors_count);
	printf("---------show doors positions----------\n\n");
	for (int i = 0; i < mlx.map.doors_count; i++)
	{
		printf("state: %d | y: %d | x: %d\n", mlx.map.doors[i].is_open, mlx.map.doors[i].y, mlx.map.doors[i].x);
	}
	
	printf("---------show doors positions----------\n\n");
	launch(&mlx);
	return (0);
}
