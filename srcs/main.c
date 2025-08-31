/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:07:56 by mait-all          #+#    #+#             */
/*   Updated: 2025/08/31 18:38:10 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int main(int ac, char **av)
{
	t_mlx_data	mlx;
	t_map	 	map;

	if (ac != 2 || !check_file_name(av[1]))
		exit (custom_error("Error:\nNo such file or directory!\n"));
	ft_bzero(&map, sizeof(t_map));
	if (!check_map(av[1], &map))
		exit (custom_error("Error:\nInvalid map!\n"));
	ft_bzero(&mlx, sizeof(t_mlx_data));
	init_player(&mlx, &map);
	launch(&mlx);
	return (0);
}
