/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linked_list_swap.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:11:12 by aurban            #+#    #+#             */
/*   Updated: 2023/11/24 16:19:58 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_llint_swap_data_front(t_llint *list)
{
	long	temp;

	if (!list || !list->head || !list->head->next)
		return ;
	temp = list->head->data;
	list->head->data = list->head->next->data;
	list->head->next->data = temp;
}
