/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:50:25 by aurban            #+#    #+#             */
/*   Updated: 2023/10/19 19:18:01 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*duplicate_str;
	size_t	len;

	len = ft_strlen(s);
	duplicate_str = malloc(len + 1);
	if (duplicate_str == NULL)
		return (NULL);
	ft_strlcpy(duplicate_str, s, len + 1);
	return (duplicate_str);
}
