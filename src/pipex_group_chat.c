/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_group_chat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 01:57:40 by aurban            #+#    #+#             */
/*   Updated: 2023/12/03 18:17:18 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clean_cmd_paths(char **cmds_path, int size)
{
	int	i;

	i = 0;
	while (i < size)
		free(cmds_path[i++]);
	free(cmds_path);
}

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
