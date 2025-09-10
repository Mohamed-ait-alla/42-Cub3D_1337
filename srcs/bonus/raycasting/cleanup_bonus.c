/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 18:39:11 by mait-all          #+#    #+#             */
/*   Updated: 2025/09/10 11:53:08 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d_bonus.h"

void	*ft_malloc(size_t size, int mode)
{
	static t_list	*head_list;
	t_list			*new_node;
	void			*content;

	new_node = NULL;
	content = NULL;
	if (mode == 1)
	{
		content = malloc(size);
		if (!content)
		{
			ft_putstr_fd("malloc Failed: ", STDERR_FILENO);
			ft_malloc(0, 0);
			exit (EXIT_FAILURE);
		}
		new_node = ft_lstnew(content);
		ft_lstadd_back(&head_list, new_node);
	}
	else if (mode == 0)
	{
		ft_lstclear(&head_list, free);
		head_list = NULL;
	}
	return (content);
}

static void	ft_destroy_textures(t_mlx_data *mlx)
{
	int	i;

	i = 0;
	while (i < 12)
	{
		if (mlx->textures[i].addr)
			mlx_destroy_image(mlx->mlx_ptr, mlx->textures[i].img);
		i++;
	}
}

int	ft_cleanup(t_mlx_data *mlx)
{
	ft_destroy_textures(mlx);
	if (mlx->mlx_ptr && mlx->mlx_window)
		mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_window);
	if (mlx->mlx_ptr)
	{
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
	}
	ft_malloc(0, 0);
	exit (EXIT_FAILURE);
}
