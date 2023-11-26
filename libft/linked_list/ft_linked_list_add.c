/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linked_list_add.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:35:02 by aurban            #+#    #+#             */
/*   Updated: 2023/11/24 16:18:07 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_nodeint	*ft_llint_data_add_back(t_llint *list, long data)
{
	t_nodeint	*node;

	node = malloc(sizeof(t_nodeint));
	if (!node || !list)
		return (NULL);
	node->data = data;
	node->next = NULL;
	if (list->last)
	{
		node->previous = list->last;
		list->last->next = node;
	}
	list->last = node;
	list->size++;
	if (list->head == NULL)
		list->head = node;
	return (node);
}

t_nodeint	*ft_llint_data_add_front(t_llint *list, long data)
{
	t_nodeint	*node;

	if (!list)
		return (NULL);
	node = malloc(sizeof(t_nodeint));
	if (!node)
		return (NULL);
	node->data = data;
	node->next = list->head;
	if (list->head)
		list->head->previous = node;
	node->previous = NULL;
	list->head = node;
	list->size++;
	return (node);
}
