/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:07:56 by mait-all          #+#    #+#             */
/*   Updated: 2025/08/04 15:25:36 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

int	ft_destroy_window(t_mlx_data *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_window);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	exit (1);
}

// void	render_wall_texture(t_mlx_data *mlx)
// {
// 	printf("hhhhhhhhhhhhhhfksjfkh\n");
// 	for (int x = 0; x < TEXTURE_WIDTH; x++)
// 	{
// 		for (int y = 0; y < TEXTURE_HIEGHT; y++)
// 		{
// 			mlx->wall_texture[(TEXTURE_WIDTH * y) + x] = (x % 8 && y % 8) ? 0x0000ff : 0x000000;
// 		}
// 	}
// }

int main()
{
	t_mlx_data	mlx;
	// mlx.wall_texture = malloc(sizeof(int) * TEXTURE_WIDTH * TEXTURE_HIEGHT);
	// render_wall_texture(&mlx);
	ft_bzero(&mlx, sizeof(t_mlx_data));
	init_player(&mlx);
	mlx.mlx_ptr = mlx_init();
	mlx.mlx_window = mlx_new_window(mlx.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "mlx window");
	if (!load_wall_texture(&mlx, "./textures/wall.xpm"))
		printf("Error: failed to load textures\n");
	mlx_hook(mlx.mlx_window, 2, 1L << 0, key_Pressed, &mlx);
	// mlx_hook(mlx.mlx_window, 3, 1L << 1, key_Released, &mlx);
	mlx_loop_hook(mlx.mlx_ptr, update, &mlx);
	mlx_hook(mlx.mlx_window, 17, 0, ft_destroy_window, &mlx);
	mlx_loop(mlx.mlx_ptr);
}
