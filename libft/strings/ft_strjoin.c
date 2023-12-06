/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:25:34 by aurban            #+#    #+#             */
/*   Updated: 2023/12/06 12:05:31 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Both strings should be valid*/
char	*ft_strjoin(const char *s1, char const *s2)
{
	char	*joined;
	size_t	joined_len;
	size_t	i;
	size_t	s1_len;

	if (!s1 || !s2)
		return (NULL);
	joined_len = 0;
	s1_len = 0;
	while (s1[s1_len])
		s1_len++;
	while (s2[joined_len])
		joined_len++;
	joined_len += s1_len;
	joined = malloc((joined_len + 1) * sizeof(char));
	if (!joined)
		return (NULL);
	joined[joined_len] = '\0';
	i = 0;
	while (s1[i++])
		joined[i - 1] = s1[i - 1];
	i = 0;
	while (s2[i++])
		joined[s1_len + i - 1] = s2[i - 1];
	return (joined);
}

/*First string can be NULL*/
char	*ft_strjoin_n(const char *s1, char const *s2)
{
	char	*joined;
	size_t	joined_len;
	size_t	i;
	size_t	s1_len;

	if (!s2)
		return (NULL);
	joined_len = 0;
	s1_len = 0;
	while (s1 && s1[s1_len])
		s1_len++;
	while (s2[joined_len])
		joined_len++;
	joined_len += s1_len;
	joined = malloc((joined_len + 1) * sizeof(char));
	if (!joined)
		return (NULL);
	joined[joined_len] = '\0';
	i = 0;
	while (s1 && s1[i++])
		joined[i - 1] = s1[i - 1];
	i = 0;
	while (s2[i++])
		joined[s1_len + i - 1] = s2[i - 1];
	return (joined);
}
