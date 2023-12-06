/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:15:51 by aurban            #+#    #+#             */
/*   Updated: 2023/12/06 12:16:32 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	***free_triple_char(char ***ccc)
{
	size_t	i;
	size_t	j;

	if (!ccc)
		return (NULL);
	i = 0;
	while (ccc[i])
	{
		j = 0;
		while (ccc[i][j])
			free(ccc[i][j++]);
		free(ccc[i++]);
	}
	free(ccc);
	return (NULL);
}

char	**free_double_char(char **cc)
{
	size_t	i;

	if (!cc)
		return (NULL);
	i = 0;
	while (cc[i])
		free(cc[i++]);
	free(cc);
	return (NULL);
}
