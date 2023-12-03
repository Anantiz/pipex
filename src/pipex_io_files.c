/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_io_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 00:16:19 by aurban            #+#    #+#             */
/*   Updated: 2023/12/03 04:22:08 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#define LOCAL_READ_SIZE 256

static void	ft_read_fd_cpy_content(char *buff, char **content, size_t *offset, ssize_t nread)
{
	ssize_t	i;
	
	i = 0;
	while (i < nread && buff[i])
	{
		*content = resize_line((*content), nread);
		if (!(*content))
			return ;
		(*content)[i + (*offset)] = buff[i];
		i++;
	}
	*offset += i;
}

char	*ft_read_fd(int fd)
{
	char	buff[LOCAL_READ_SIZE];
	char	*content;
	size_t	offset;
	ssize_t	nread;

	nread = 1;
	offset = 0;
	content = NULL;
	while (nread != 0)
	{
		nread = read(fd, buff, LOCAL_READ_SIZE);
		if (nread < 0)
		{
			free(content);
			return (NULL);
		}
		if (nread)
			ft_read_fd_cpy_content(buff, &content, &offset, nread);
		if (!content)
			return (NULL);
	}
	return (content);
}

char	*write_infile_to_buff(char *infile_path)
{
	int		fd;
	char	*content;
	
	if (!infile_path)
		return (NULL);
	fd = open(infile_path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	content = ft_read_fd(fd);
	close(fd);
	return (content);
}

ssize_t	ft_write_fd(int fd, char *content)
{
	size_t	len;
	ssize_t	nwrite;

	if (!content)
		return (0);
	len = ft_strlen(content);
	nwrite = write(fd, content, len);
	return (nwrite);
}

ssize_t	write_buff_to_outfile(char *outfile_path, char *buffer)
{
	int		fd;
	ssize_t	nwrite;
	
	if (!outfile_path || !buffer)
		return (-1);
	fd = open(outfile_path, O_WRONLY | O_CREAT | O_TRUNC, 0644); // Check permission shit
	if (fd == -1)
		return (-1);
	nwrite = ft_write_fd(fd, buffer);
	if (nwrite < 0)
		ft_printf_fd(2, "Write Error, could not write to file\n");
	else if (nwrite != (ssize_t)ft_strlen(buffer))
		ft_printf_fd(2, "Write Error, couldn't write full buffer\n");
	close(fd);
	return (nwrite);
}
