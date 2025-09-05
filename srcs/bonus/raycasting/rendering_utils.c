/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:41:17 by mait-all          #+#    #+#             */
/*   Updated: 2025/09/04 19:07:14 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	put_pixel(t_mlx_data *mlx, int x, int y, int color)
{
	int	offset;

	if (x < 0 || x >= mlx->window_width || y < 0 || y >= mlx->window_height)
		return ;
	offset = (y * mlx->size_line) + (x * (mlx->bpp / 8));
	*(unsigned int *)(mlx->img_pixels + offset) = color;
}

int	get_texture_pixel(t_mlx_data *mlx, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= mlx->wall_texture->width
		|| y < 0 || y >= mlx->wall_texture->height)
		return (0x000000);
	dst = mlx->wall_texture->addr + (y * mlx->wall_texture->line_length
			+ x * (mlx->wall_texture->bpp / 8));
	return (*(unsigned int *)dst);
}

t_texture	*get_wall_texture(t_mlx_data *mlx, int x)
{
	if (mlx->rays[x].was_hit_door)
		return (&mlx->textures[4]);
	else if (mlx->rays[x].was_hit_vert)
	{
		if (is_ray_facing_right(mlx->rays[x].ray_angle))
			return (&mlx->textures[3]);
		else
			return (&mlx->textures[2]);
	}
	else if (mlx->rays[x].was_hit_horz)
	{
		if (is_ray_facing_down(mlx->rays[x].ray_angle))
			return (&mlx->textures[1]);
		else
			return (&mlx->textures[0]);
	}
	return (NULL);
}
