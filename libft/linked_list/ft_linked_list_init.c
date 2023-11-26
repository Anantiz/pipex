/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linked_list_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:22:10 by aurban            #+#    #+#             */
/*   Updated: 2023/11/23 17:44:30 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_llint	*ft_llint_new(void)
{
	t_llint	*list;

	list = malloc(sizeof(t_llint));
	if (!list)
		return (NULL);
	list->head = NULL;
	list->last = NULL;
	list->size = 0;
	return (list);
}
