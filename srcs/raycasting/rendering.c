/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 10:04:48 by mait-all          #+#    #+#             */
/*   Updated: 2025/07/28 20:36:19 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

void put_pixel(t_mlx_data *mlx, int x, int y, int color)
{
    if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
        return;

    int offset = (y * mlx->size_line) + (x * (mlx->bpp / 8));
    *(unsigned int *)(mlx->img_pixels + offset) = color;
}


void	draw_circle(t_mlx_data *mlx, int cx, int cy, int radius, int color)
{
	for (int y = -radius; y <= radius; y++)
		for (int x = -radius; x <= radius; x++)
			if (x * x + y * y <= radius * radius)
				put_pixel(mlx, cx + x, cy + y, color);
}

void draw_square(t_mlx_data *mlx, int x, int y, int color)
{
	for (int i = 0; i < 32; i++) // height
	{
		for (int j = 0; j < 32; j++) // width
		{
			put_pixel(mlx, x + j, y + i, color);
		}
	}
}

void draw_line(t_mlx_data *mlx, int x0, int y0, int x1, int y1, int color)
{
    int dx = x1 - x0;
    int dy = y1 - y0;

    int steps = fmax(abs(dx), abs(dy));

    double x_inc = dx / (double)steps;
    double y_inc = dy / (double)steps;

    double x = x0;
    double y = y0;

    for (int i = 0; i <= steps; i++)
    {
         put_pixel(mlx, round(x), round(y), color);
        x += x_inc;
        y += y_inc;
    }
}

void draw_facing_line(t_mlx_data *mlx, double length, double color)
{
    double x0 = mlx->player.player_x;
    double y0 = mlx->player.player_y;

    double x1 = x0 + cos(mlx->player.rotation_Angle) * length;
    double y1 = y0 + sin(mlx->player.rotation_Angle) * length;

    draw_line(mlx, x0, y0, x1, y1, color); // red line
}

void draw_vertical_line(t_mlx_data *mlx, int x, int wall_top, int wall_bottom, int color)
{
    for (int y = 0; y < WINDOW_HEIGHT; y++) {
        if (y < wall_top)
            put_pixel(mlx, x, y, 0x000000);
        else if (y >= wall_top && y <= wall_bottom)
            put_pixel(mlx, x, y, color); // Wall slice
        else
            put_pixel(mlx, x, y, 0xffffff);
    }
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

	i = 0;
	while (i < MAP_NUM_ROWS)
	{
		j = 0;
		while (j < MAP_NUM_COLS)
		{
			if (map[i][j] == '1')
				draw_square(mlx, j * TILE_SIZE, i * TILE_SIZE, 0x0000ff);
			else
				draw_square(mlx, j * TILE_SIZE, i * TILE_SIZE, 0x000000);
			j++;
		}
		i++;
	}
	draw_circle(mlx, mlx->player.player_x, mlx->player.player_y, 3, 0xff0000);
	draw_facing_line(mlx, 16, 0xff0000);
}

void	render_projected_walls(t_mlx_data *mlx)
{
	int		i;
	double	wall_strip_height;
	double	projection_plane_distance;

	i = 0;
	while (i < NUM_RAYS)
	{
		projection_plane_distance = (WINDOW_WIDTH / 2) / tan(FOV / 2);
		wall_strip_height = (TILE_SIZE / mlx->rays[i].ray_distance) * projection_plane_distance;
		draw_vertical_line(mlx, i, (WINDOW_HEIGHT / 2) - (wall_strip_height / 2), (WINDOW_HEIGHT / 2) + (wall_strip_height / 2), 0xa000ff);
		i++;
	}
}

int update(t_mlx_data *mlx)
{
    mlx->img = mlx_new_image(mlx->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
    mlx->img_pixels = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->size_line, &mlx->endian);
	// render(mlx);
	render_projected_walls(mlx);
	cast_rays(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_window, mlx->img, 0, 0);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img);
    return (0);
}
