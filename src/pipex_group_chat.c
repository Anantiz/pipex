/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_group_chat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 01:57:40 by aurban            #+#    #+#             */
/*   Updated: 2023/12/03 17:28:36 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

ssize_t	write_buffer_to_child(char *buff, int fd)
{
	ssize_t	nwrite;

	if (!buff)
	{
		write(fd, "\0", 1);
		ft_printf("AAAAA\n");
		return (-1);
	}
	nwrite = ft_write_fd(fd, buff);
	return (nwrite);
}

char	*write_child_to_buffer(char *buff, int fd)
{
	free(buff);
	buff = ft_read_fd(fd);
	return (buff);
}
