/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:07:56 by mait-all          #+#    #+#             */
/*   Updated: 2025/08/28 18:13:53 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_destroy_window(t_mlx_data *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_window);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	exit (0);
}

int main(int ac, char **av)
{
	t_mlx_data	mlx;
	t_map		map;

	// check file name
	if (ac != 2 || !check_file_name(av[1]))
		return (custom_error("Error:\nNo such file or directory!\n"), 1);
		// check the map
	ft_bzero(&map, sizeof(t_map));
	if (!check_map(av[1], &map))
		return (custom_error("Error:\nInvalid map!\n"), 1);
	// render_wall_texture(&mlx);
	ft_bzero(&mlx, sizeof(t_mlx_data));
	mlx.map = map;
	init_player(&mlx);
	printf("px: %f, py: %f\n", mlx.player.px, mlx.player.py);
	mlx.mlx_ptr = mlx_init();
	mlx.mlx_window = mlx_new_window(mlx.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "mlx window");

	if (!load_wall_texture(&mlx, "./textures/wall.xpm"))
	{
		printf("Error: failed to load textures\n");
		exit (1);
	}
	mlx_hook(mlx.mlx_window, 2, 1L << 0, key_pressed, &mlx);
	mlx_hook(mlx.mlx_window, 3, 1L << 1, key_released, &mlx);
	mlx_loop_hook(mlx.mlx_ptr, update, &mlx);
	mlx_hook(mlx.mlx_window, 17, 0, ft_destroy_window, &mlx);
	mlx_loop(mlx.mlx_ptr);
}
