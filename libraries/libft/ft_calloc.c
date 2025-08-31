/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:33:37 by mait-all          #+#    #+#             */
/*   Updated: 2025/08/30 18:53:58 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (size && count > (size_t) -1 / size)
		return (NULL);
	ptr = (void *)ft_malloc(size * count, 1);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}
