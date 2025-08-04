/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 10:04:48 by mait-all          #+#    #+#             */
/*   Updated: 2025/08/04 15:47:37 by mait-all         ###   ########.fr       */
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

int	load_wall_texture(t_mlx_data *mlx, char *path)
{
	mlx->wall_texture.img = mlx_xpm_file_to_image (mlx->mlx_ptr, path, &mlx->wall_texture.width, &mlx->wall_texture.height);
	if (!mlx->wall_texture.img)
		printf("failed to load the wall texture\n");
	mlx->wall_texture.addr = mlx_get_data_addr(mlx->wall_texture.img, &mlx->wall_texture.bpp, &mlx->wall_texture.line_length, &mlx->wall_texture.endian);
	if (!mlx->wall_texture.addr)
		printf("failed to get the addr of the texture\n");
	printf("texture loaded successfully\n");
	return (1);
}

int get_texture_pixel(t_mlx_data *mlx, int x, int y)
{
	char *dst;

  if (x < 0 || x >= mlx->wall_texture.width || y < 0 || y >= mlx->wall_texture.height)
        return (0x000000); // Return black for out-of-bounds
    
    dst = mlx->wall_texture.addr + (y * mlx->wall_texture.line_length + x * (mlx->wall_texture.bpp / 8));
    return (*(unsigned int*)dst);
}

int calculate_texture_x(t_mlx_data *mlx, int ray_index)
{
    t_ray *ray = &mlx->rays[ray_index];
    double wall_x;
    int texture_x;
    
    // Use the fractional part of the wall hit position
    wall_x = ray->wall_hit_x - floor(ray->wall_hit_x);
    if (wall_x < 0) wall_x += 1.0;
    
    // If hitting a vertical wall, use Y coordinate instead
    if (fabs(ray->wall_hit_x - floor(ray->wall_hit_x + 0.5)) < 0.01)
    {
        wall_x = ray->wall_hit_y - floor(ray->wall_hit_y);
        if (wall_x < 0) wall_x += 1.0;
    }
    
    texture_x = (int)(wall_x * mlx->wall_texture.width);
    
    if (texture_x >= mlx->wall_texture.width)
        texture_x = mlx->wall_texture.width - 1;
    
    return (texture_x);
}

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

void draw_textured_vertical_line(t_mlx_data *mlx, int wall_top, 
                                int wall_bottom, int x)
{
    int texture_x = calculate_texture_x(mlx, x);
    int wall_height = wall_bottom - wall_top;
    
    for (int y = 0; y < WINDOW_HEIGHT; y++) 
    {
        if (y < wall_top)
        {
            // Ceiling
            put_pixel(mlx, x, y, 0x87CEEB); // Sky blue ceiling
        }
        else if (y >= wall_top && y <= wall_bottom)
        {
			// Wall rendering
			
            // Calculate which pixel of the texture to use
            double texture_y_exact = (double)(y - wall_top) / wall_height * mlx->wall_texture.height;
            int texture_y = (int)texture_y_exact;
            
            // Bounds checking
            if (texture_y >= mlx->wall_texture.height)
                texture_y = mlx->wall_texture.height - 1;
            if (texture_y < 0)
                texture_y = 0;
            
            // Get the color from texture
            int color = get_texture_pixel(mlx, texture_x, texture_y);
            
            // Apply distance-based shading
            color = apply_distance_shading(color, mlx->rays[x].ray_correct_distance);
            
            put_pixel(mlx, x, y, color);
        }
        else
        {
            // Floor
            put_pixel(mlx, x, y, 0x8B4513); // Brown floor
        }
    }
}



void render_textured_walls(t_mlx_data *mlx)
{
    int i;
    double wall_strip_height;
    double projection_plane_distance;

    i = 0;
    while (i < NUM_RAYS)
    {
        projection_plane_distance = (WINDOW_WIDTH / 2) / tan(FOV / 2);
        wall_strip_height = (TILE_SIZE / mlx->rays[i].ray_correct_distance) * projection_plane_distance;
        
        // Use textured drawing instead of solid color
        draw_textured_vertical_line(mlx,
                                   (WINDOW_HEIGHT / 2) - (wall_strip_height / 2), 
                                   (WINDOW_HEIGHT / 2) + (wall_strip_height / 2), 
                                   i);
        i++;
    }
}


// void draw_facing_line(t_mlx_data *mlx, double length, double color)
// {
//     double x0 = mlx->player.player_x;
//     double y0 = mlx->player.player_y;

//     double x1 = x0 + cos(mlx->player.rotation_Angle) * length;
//     double y1 = y0 + sin(mlx->player.rotation_Angle) * length;

//     draw_line(mlx, x0, y0, x1, y1, color); // red line
// }

// void draw_vertical_line(t_mlx_data *mlx, int x, int wall_top, int wall_bottom, int color)
// {
//     for (int y = 0; y < WINDOW_HEIGHT; y++) {
//         if (y < wall_top)
//             put_pixel(mlx, x, y, 0x000000);
//         else if (y >= wall_top && y <= wall_bottom)
//             put_pixel(mlx, x, y, color); // Wall slice
//         else
//             put_pixel(mlx, x, y, 0xffffff);
//     }
// }


// void	render(t_mlx_data *mlx)
// {
// 	char	map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
// 		{'1', '1', '1', '1', '1', '1', '1', '1'},
// 		{'1', '0', '0', '0', '1', '0', '0', '1'},
// 		{'1', '1', '1', '0', '0', '0', '0', '1'},
// 		{'1', '0', '0', '0', '0', '1', '1', '1'},
// 		{'1', '0', '0', '0', '0', '0', '0', '1'},
// 		{'1', '1', '1', '1', '1', '1', '1', '1'},
// 	};
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < MAP_NUM_ROWS)
// 	{
// 		j = 0;
// 		while (j < MAP_NUM_COLS)
// 		{
// 			if (map[i][j] == '1')
// 				draw_square(mlx, j * TILE_SIZE, i * TILE_SIZE, 0x0000ff);
// 			else
// 				draw_square(mlx, j * TILE_SIZE, i * TILE_SIZE, 0x000000);
// 			j++;
// 		}
// 		i++;
// 	}
// 	draw_circle(mlx, mlx->player.player_x, mlx->player.player_y, 3, 0xff0000);
// 	draw_facing_line(mlx, 16, 0xff0000);
// }

// void	render_projected_walls(t_mlx_data *mlx)
// {
// 	int		i;
// 	double	wall_strip_height;
// 	double	projection_plane_distance;

// 	i = 0;
// 	while (i < NUM_RAYS)
// 	{
// 		projection_plane_distance = (WINDOW_WIDTH / 2) / tan(FOV / 2);
// 		wall_strip_height = (TILE_SIZE / mlx->rays[i].ray_correct_distance) * projection_plane_distance;
// 		draw_vertical_line(mlx, i, (WINDOW_HEIGHT / 2) - (wall_strip_height / 2), (WINDOW_HEIGHT / 2) + (wall_strip_height / 2), 0x0000ff);
// 		i++;
// 	}
// }

int update(t_mlx_data *mlx)
{
    mlx->img = mlx_new_image(mlx->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
    mlx->img_pixels = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->size_line, &mlx->endian);
	// render(mlx);
	cast_rays(mlx);
	// render_projected_walls(mlx);
	render_textured_walls(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_window, mlx->img, 0, 0);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img);
    return (0);
}
