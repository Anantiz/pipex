/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_group_chat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 01:57:40 by aurban            #+#    #+#             */
/*   Updated: 2023/12/04 21:52:53 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

ssize_t	write_buffer_to_child(char *buff, int fd)
{
	ssize_t	nwrite;

	if (!buff)
		return (-1);
	nwrite = ft_write_fd(fd, buff);
	return (nwrite);
}

char	*write_child_to_buffer(char *buff, int fd)
{
	free(buff);
	buff = ft_read_fd(fd);
	return (buff);
}
