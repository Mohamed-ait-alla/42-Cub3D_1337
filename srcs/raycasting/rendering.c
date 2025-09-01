/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 10:04:48 by mait-all          #+#    #+#             */
/*   Updated: 2025/09/01 15:47:54 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void put_pixel(t_mlx_data *mlx, int x, int y, int color)
{
    if (x < 0 || x >= mlx->window_width || y < 0 || y >= mlx->window_height)
        return;

    int offset = (y * mlx->size_line) + (x * (mlx->bpp / 8));
    *(unsigned int *)(mlx->img_pixels + offset) = color;
}

int get_texture_pixel(t_mlx_data *mlx, int x, int y)
{
	char *dst;

  if (x < 0 || x >= mlx->wall_texture->width || y < 0 || y >= mlx->wall_texture->height)
        return (0x000000);
    
    dst = mlx->wall_texture->addr + (y * mlx->wall_texture->line_length + x * (mlx->wall_texture->bpp / 8));
    return (*(unsigned int*)dst);
}

// used just to add some dark colors to the walls
int apply_distance_shading(int color, double distance)
{
    double max_distance = 500.0;
    double shade_factor = 1.0 - (distance / max_distance);

    if (shade_factor < 0.3) shade_factor = 0.3;
    if (shade_factor > 1.0) shade_factor = 1.0;
    int r = (color >> 16) & 0xFF;
    int g = (color >> 8) & 0xFF;
    int b = color & 0xFF;
    r = (int)(r * shade_factor);
    g = (int)(g * shade_factor);
    b = (int)(b * shade_factor);
    return ((r << 16) | (g << 8) | b);
}

t_texture	*get_wall_texture(t_mlx_data *mlx, int x)
{
	if (mlx->rays[x].was_hit_vert)
	{
		if (is_ray_facing_right(mlx->rays[x].ray_angle))
			return (&mlx->textures[3]);
		else
			return (&mlx->textures[2]);
	}
	if (mlx->rays[x].was_hit_horz)
	{
		if (is_ray_facing_down(mlx->rays[x].ray_angle))
			return (&mlx->textures[1]);
		else
			return (&mlx->textures[0]);
	}
	return (NULL);
}

void draw_textured_vertical_line(t_mlx_data *mlx, int wall_top, 
                                int wall_bottom, int x, double wall_strip_height)
{
	int color;
	int texture_offset_x;
	int texture_offset_y;
	int	y;

	y = 0;
	mlx->wall_texture = get_wall_texture(mlx, x);
	if (!mlx->wall_texture)
	{
		perror("Error: Failed to get the wall_texture!\n");
		return ;
	}
	// get the x offset
	if (mlx->rays[x].was_hit_vert)
		texture_offset_x = (int)mlx->rays[x].wall_hit_y % TILE_SIZE;
	else
		texture_offset_x = (int)mlx->rays[x].wall_hit_x % TILE_SIZE;
	while (y < mlx->window_height)
    {
		// Ceiling
        if (y < wall_top)
			put_pixel(mlx, x, y, mlx->map.ceiling_color);
		// Wall rendering
        else if (y >= wall_top && y <= wall_bottom)
        {
			// get the y offset
			texture_offset_y = (y -  wall_top) * ((float)mlx->wall_texture->height / wall_strip_height);
            // Bounds checking
            if (texture_offset_y >= mlx->wall_texture->height)
                texture_offset_y = mlx->wall_texture->height - 1;
            if (texture_offset_y < 0)
                texture_offset_y = 0;
            
            // // Get the color from texture
            color = get_texture_pixel(mlx, texture_offset_x, texture_offset_y);
            
            // // Apply distance-based shading
            color = apply_distance_shading(color, mlx->rays[x].ray_correct_distance);
			put_pixel(mlx, x, y, color);	

        }
		// Floor
        else
            put_pixel(mlx, x, y, mlx->map.floor_color);

		y++;
    }
}

void render_textured_walls(t_mlx_data *mlx)
{
    int i;
    double wall_strip_height;
    double projection_plane_distance;

    i = 0;
    while (i < mlx->nb_rays)
    {
        projection_plane_distance = (mlx->window_width / 2) / tan(FOV / 2);
        wall_strip_height = (TILE_SIZE / mlx->rays[i].ray_correct_distance) * projection_plane_distance;
        
        // Use textured drawing instead of solid color
        draw_textured_vertical_line(mlx,
                                   (mlx->window_height / 2) - (wall_strip_height / 2), 
                                   (mlx->window_height / 2) + (wall_strip_height / 2), 
                                   i, wall_strip_height);
        i++;
    }
}

int update(t_mlx_data *mlx)
{
	update_player_position(mlx);
    mlx->img = mlx_new_image(mlx->mlx_ptr, mlx->window_width, mlx->window_height);
    mlx->img_pixels = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->size_line, &mlx->endian);
	// render(mlx);
	cast_rays(mlx);
	render_textured_walls(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_window, mlx->img, 0, 0);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img);
    return (0);
}
