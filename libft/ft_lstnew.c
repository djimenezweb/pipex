/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:39:16 by danielji          #+#    #+#             */
/*   Updated: 2025/04/20 17:15:18 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Allocates memory and returns a new node.
The `content` variable is initialized with the given parameter `content`.
The variable `next` is initialized to `NULL`. */
t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
	{
		return ((void *)0);
	}
	node->content = content;
	node->next = (void *)0;
	return (node);
}
