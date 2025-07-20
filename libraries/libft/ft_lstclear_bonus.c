/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahani <mdahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:01:57 by mait-all          #+#    #+#             */
/*   Updated: 2025/05/17 19:55:41 by mdahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current_node;
	t_list	*next_node;

	if (!lst || !del || !(*lst))
		return ;
	current_node = *lst;
	while (current_node)
	{
		next_node = current_node->next;
		if (current_node->content)
			del(current_node->content);
		free(current_node);
		current_node = next_node;
	}
	*lst = NULL;
}
