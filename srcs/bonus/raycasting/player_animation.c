/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_animation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 13:25:03 by mait-all          #+#    #+#             */
/*   Updated: 2025/09/07 14:46:13 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

void	put_gun(t_mlx_data *mlx, int start_x, int start_y, int anim_index)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	mlx->wall_texture = &mlx->textures[anim_index];
	while (y < mlx->textures[anim_index].height)
	{
		x = 0;
		while (x < mlx->textures[anim_index].width)
		{
			color = get_texture_pixel(mlx, x, y);
			if ((unsigned int)color != 0xFF000000)
				put_pixel(mlx, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
}

void	render_gun(t_mlx_data *mlx)
{
	int	x;
	int	y;

	x = (WINDOW_WIDTH / 2) - (mlx->textures[mlx->player.anim_index].width / 2);
	y = (WINDOW_HEIGHT) - mlx->textures[mlx->player.anim_index].height;
	put_gun(mlx, x, y, mlx->player.anim_index);
}

double	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

void	update_player_animation(t_mlx_data *mlx)
{
	static double	last_time;
	double			now;

	now = get_time();
	if (mlx->player.is_animating)
	{
		if (now - last_time > 0.05)
		{
			mlx->player.anim_index++;
			if (mlx->player.anim_index > 9)
			{
				mlx->player.anim_index = 5;
				mlx->player.is_animating = 0;
			}
			last_time = now;
		}
	}
}
