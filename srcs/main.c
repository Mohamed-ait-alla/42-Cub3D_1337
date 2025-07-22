/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:07:56 by mait-all          #+#    #+#             */
/*   Updated: 2025/07/22 10:30:26 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

int	ft_close_window(t_mlx_data *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_window);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	exit (1);
}

int main()
{
	t_mlx_data	mlx;

	mlx.mlx_ptr = mlx_init();
	mlx.mlx_window = mlx_new_window(mlx.mlx_ptr, 500, 500, "mlx window");
	
	mlx_hook(mlx.mlx_window, 17, 0, ft_close_window, &mlx);
	mlx_loop(mlx.mlx_ptr);
}