/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 10:04:48 by mait-all          #+#    #+#             */
/*   Updated: 2025/09/02 15:41:42 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_wall(t_mlx_data *mlx,
					int x, int texture_offset_x,
					double wall_strip_height)
{
	int	y;
	int	texture_offset_y;
	int	color;

	y = 0;
	while (y < mlx->window_height)
	{
		if (y < mlx->wall_top)
			put_pixel(mlx, x, y, mlx->map.ceiling_color);
		else if (y >= mlx->wall_top && y <= mlx->wall_bottom)
		{
			texture_offset_y = (y - mlx->wall_top)
				* ((float)mlx->wall_texture->height / wall_strip_height);
			if (texture_offset_y >= mlx->wall_texture->height)
				texture_offset_y = mlx->wall_texture->height - 1;
			if (texture_offset_y < 0)
				texture_offset_y = 0;
			color = get_texture_pixel(mlx, texture_offset_x, texture_offset_y);
			put_pixel(mlx, x, y, color);
		}
		else
			put_pixel(mlx, x, y, mlx->map.floor_color);
		y++;
	}
}

void	draw_walls(t_mlx_data *mlx, int x,
										double wall_strip_height)
{
	int	texture_offset_x;

	mlx->wall_texture = get_wall_texture(mlx, x);
	if (!mlx->wall_texture)
	{
		perror("Error: Failed to get the wall_texture!\n");
		return ;
	}
	if (mlx->rays[x].was_hit_vert)
		texture_offset_x = (int)mlx->rays[x].wall_hit_y % TILE_SIZE;
	else
		texture_offset_x = (int)mlx->rays[x].wall_hit_x % TILE_SIZE;
	draw_wall(mlx, x, texture_offset_x, wall_strip_height);
}

void	render_textured_walls(t_mlx_data *mlx)
{
	int		i;
	double	wall_strip_height;
	double	projection_plane_distance;

	i = 0;
	while (i < mlx->nb_rays)
	{
		projection_plane_distance = (mlx->window_width / 2) / tan(FOV / 2);
		wall_strip_height = (TILE_SIZE / mlx->rays[i].ray_correct_distance)
			* projection_plane_distance;
		mlx->wall_top = (mlx->window_height / 2) - (wall_strip_height / 2);
		mlx->wall_bottom = (mlx->window_height / 2) + (wall_strip_height / 2);
		draw_walls(mlx, i, wall_strip_height);
		i++;
	}
}

int	update(t_mlx_data *mlx)
{
	update_player_position(mlx);
	mlx->img = mlx_new_image(mlx->mlx_ptr,
			mlx->window_width, mlx->window_height);
	mlx->img_pixels = mlx_get_data_addr(mlx->img,
			&mlx->bpp, &mlx->size_line, &mlx->endian);
	cast_rays(mlx);
	render_textured_walls(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_window, mlx->img, 0, 0);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img);
	return (0);
}
