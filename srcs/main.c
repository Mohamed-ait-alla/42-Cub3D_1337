/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:07:56 by mait-all          #+#    #+#             */
/*   Updated: 2025/07/24 10:15:45 by mait-all         ###   ########.fr       */
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

int	key_Pressed(int keycode, t_mlx_data *mlx)
{
	if (keycode == XK_Escape)
	ft_destroy_window(mlx);
	else if (keycode == XK_w || keycode == XK_Up)
	mlx->player.walk_dir = 1;
	else if (keycode == XK_s || keycode == XK_Down)
	mlx->player.walk_dir = -1;
	else if (keycode == XK_a || keycode == XK_Left)
	mlx->player.turn_dir = -1;
	else if (keycode == XK_d || keycode == XK_Right)
	mlx->player.turn_dir = 1;
	printf("walk_dir is %d\n", mlx->player.walk_dir);
	printf("turn_dir is %d\n", mlx->player.turn_dir);
	return (0);
}

void	init_player(t_mlx_data *mlx)
{
	mlx->player.player_x = WINDOW_WIDTH / 2;
	mlx->player.player_y = WINDOW_HEIGHT / 2;
	mlx->player.turn_dir = 0;
	mlx->player.walk_dir = 0;
	mlx->player.rotation_Angle = PI / 2;
	mlx->player.rotation_speed = 2 * (PI / 180);
	mlx->player.move_speed = 2.0;
}

void	render(t_mlx_data *mlx)
{
	char	map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
		{'1', '1', '1', '1', '1', '1', '1', '1'},
		{'1', '0', '0', '0', '1', '0', '0', '1'},
		{'1', '1', '1', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '1', '1', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '1', '1', '1', '1', '1', '1', '1'},
	};
	int	i;
	int	j;
	int	size;
	
	size = 32;
	mlx->wall = mlx_xpm_file_to_image(mlx->mlx_ptr, "../textures/wall.xpm", &size, &size);
	if (!mlx->wall)
	 exit (120);
	mlx->black = mlx_xpm_file_to_image(mlx->mlx_ptr, "../textures/black.xpm", &size, &size);
	if (!mlx->black)
		exit (130);
	i = 0;
	while (i < MAP_NUM_ROWS)
	{
		j = 0;
		while (j < MAP_NUM_COLS)
		{
			if (map[i][j] == '1')
				mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_window, mlx->wall, j * size, i * size);
			else
				mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_window, mlx->black, j * size, i * size);
			j++;
		}
		i++;
	}
}


int main()
{
	t_mlx_data	mlx;
	// t_player	player;

	ft_bzero(&mlx, sizeof(t_mlx_data));
	// mlx.player = malloc(1 * sizeof (t_player));
	// if (!mlx.player)
	// 	return (1);
	init_player(&mlx);
	mlx.mlx_ptr = mlx_init();
	mlx.mlx_window = mlx_new_window(mlx.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "mlx window");
	render(&mlx);
	mlx_key_hook(mlx.mlx_window, key_Pressed, &mlx);
	mlx_hook(mlx.mlx_window, 17, 0, ft_destroy_window, &mlx);
	mlx_loop(mlx.mlx_ptr);
}