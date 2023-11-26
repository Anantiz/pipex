/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linked_list_del.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:42:16 by aurban            #+#    #+#             */
/*   Updated: 2023/11/24 16:23:39 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_llint_del_node(t_llint *list, t_nodeint *node)
{
	if (!node || !list)
		return (NULL);
	if (node == list->head)
		list->head = node->next;
	if (node == list->last)
		list->last = node->previous;
	if (node->next)
		node->next->previous = node->previous;
	if (node->previous)
		node->previous->next = node->next;
	free(node);
	list->size--;
	return (NULL);
}

void	*ft_llint_del_list(t_llint *list)
{
	t_nodeint	*node;
	t_nodeint	*next;

	if (!list)
		return (NULL);
	node = list->head;
	while (node)
	{
		next = node->next;
		free(node);
		node = next;
	}
	free(list);
	return (NULL);
}
