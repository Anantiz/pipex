/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:54:26 by aurban            #+#    #+#             */
/*   Updated: 2023/11/19 12:53:24 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!s1 || !s2)
		return (-1000);
	if (!n)
		return (0);
	i = 0;
	while (i < n - 1 && s1[i] == s2[i] && (s1[i] || s2[i]))
		i++;
	return ((int)((unsigned char)s1[i] - (unsigned char)s2[i]));
}
