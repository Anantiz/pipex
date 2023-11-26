/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:15:02 by aurban            #+#    #+#             */
/*   Updated: 2023/11/12 16:12:32 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Flushes the buffer to the file descriptor and update t_buffer_data
*/
void	ft_flush(int fd, char *buffer, t_bd *bd)
{
	bd->written += bd->offset;
	write(fd, buffer, bd->offset);
	bd->offset = 0;
}

static const char	*rf2(t_bd *bd, const char *s, char *buffer, va_list *args)
{
	int	temp_read;

	if (bd->offset == SBUFSIZ)
		ft_flush(1, buffer, bd);
	if (*s == '\n')
	{
		buffer[bd->offset++] = *(s++);
		ft_flush(1, buffer, bd);
	}
	else if (*s == '%')
	{
		temp_read = 1;
		while (s[temp_read] == ' ')
			temp_read++;
		if (ft_arg_to_buffer(buffer, bd, args, s[temp_read]) == -1)
			ft_send_char(buffer, bd, *s);
		else
			s += temp_read;
		s++;
	}
	else
		buffer[bd->offset++] = *(s++);
	return (s);
}

static int	read_format(const char *s, va_list *args)
{
	char	buffer[SBUFSIZ];
	t_bd	bd;

	bd.offset = 0;
	bd.written = 0;
	while (*s)
	{
		s = rf2(&bd, s, buffer, args);
	}
	ft_flush(1, buffer, &bd);
	return (bd.written);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		check;

	check = 0;
	if (!format)
		return (-1);
	va_start(args, format);
	check = read_format(format, &args);
	va_end(args);
	return (check);
}
