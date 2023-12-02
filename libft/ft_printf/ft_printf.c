/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:15:02 by aurban            #+#    #+#             */
/*   Updated: 2023/12/02 22:25:10 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Flushes the buffer to the file descriptor and update t_buffer_data
*/
void	ft_flush(char *buffer, t_bd *bd)
{
	bd->written += bd->offset;
	bd->error = (int)write(bd->fd, buffer, bd->offset);
	bd->offset = 0;
}

/*
rf2 = read_format_2
*/
static const char	*rf2(t_bd *bd, const char *s, char *buffer, va_list *args)
{
	int	temp_read;

	if (bd->offset == SBUFSIZ)
		ft_flush(buffer, bd);
	if (*s == '\n')
	{
		buffer[bd->offset++] = *(s++);
		ft_flush(buffer, bd);
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

int	ft_printf(const char *format, ...)
{
	va_list	args;
	t_bd	bd;
	char	buffer[SBUFSIZ];

	if (!format)
		return (-1);
	va_start(args, format);
	bd.offset = 0;
	bd.written = 0;
	bd.error = 0;
	bd.fd = 1;
	while (*format)
		format = rf2(&bd, format, buffer, &args);
	ft_flush(buffer, &bd);
	va_end(args);
	return (bd.written);
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	va_list	args;
	t_bd	bd;
	char	buffer[SBUFSIZ];

	if (!format)
		return (-1);
	va_start(args, format);
	bd.offset = 0;
	bd.written = 0;
	bd.error = 0;
	bd.fd = fd;
	while (*format)
		format = rf2(&bd, format, buffer, &args);
	ft_flush(buffer, &bd);
	va_end(args);
	return (bd.written);
}
