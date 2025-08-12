/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:07:56 by mait-all          #+#    #+#             */
/*   Updated: 2025/08/12 18:59:28 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

int	ft_destroy_window(t_mlx_data *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_window);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	exit (0);
}

int main()
{
	t_mlx_data	mlx;

	// render_wall_texture(&mlx);
	ft_bzero(&mlx, sizeof(t_mlx_data));
	init_player(&mlx);
	mlx.mlx_ptr = mlx_init();
	mlx.mlx_window = mlx_new_window(mlx.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "mlx window");
	if (!load_wall_texture(&mlx, "./textures/tile39.xpm"))
	{
		printf("Error: failed to load textures\n");
		exit (1);
	}
	mlx_hook(mlx.mlx_window, 2, 1L << 0, key_pressed, &mlx);
	mlx_hook(mlx.mlx_window, 3, 1L << 1, key_released, &mlx);
	// mlx_hook(mlx.mlx_window, 3, 1L << 1, key_Released, &mlx);
	mlx_loop_hook(mlx.mlx_ptr, update, &mlx);
	mlx_hook(mlx.mlx_window, 17, 0, ft_destroy_window, &mlx);
	mlx_loop(mlx.mlx_ptr);
}
