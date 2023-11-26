/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_to_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:06:49 by aurban            #+#    #+#             */
/*   Updated: 2023/11/23 16:23:22 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_send_char(char *buffer, t_bd *bd, char c)
{
	if (bd->offset == SBUFSIZ)
		ft_flush(1, buffer, bd);
	if (c == '\n')
	{
		buffer[bd->offset++] = c;
		ft_flush(1, buffer, bd);
	}
	else
		buffer[bd->offset++] = c;
}

void	ft_send_str(char *buffer, t_bd *bd, const char *str)
{
	if (!str)
	{
		ft_send_char(buffer, bd, '(');
		ft_send_char(buffer, bd, 'n');
		ft_send_char(buffer, bd, 'u');
		ft_send_char(buffer, bd, 'l');
		ft_send_char(buffer, bd, 'l');
		return (ft_send_char(buffer, bd, ')'));
	}
	while (*str)
	{
		if (bd->offset == SBUFSIZ)
			ft_flush(1, buffer, bd);
		if (*str == '\n')
		{
			buffer[bd->offset++] = *(str++);
			ft_flush(1, buffer, bd);
		}
		else
			buffer[bd->offset++] = *(str++);
	}
}

void	ft_send_ptr(char *buffer, t_bd *bd, void *ptr)
{
	char	*str;

	ft_send_char(buffer, bd, '0');
	ft_send_char(buffer, bd, 'x');
	if (ptr == NULL)
	{
		ft_send_char(buffer, bd, '0');
		return ;
	}
	str = ft_ultohex((unsigned long) ptr);
	ft_send_str(buffer, bd, str);
	free(str);
}

void	ft_send_decimal(char *buffer, t_bd *bd, long long n)
{
	char	*n_str;

	n_str = ft_lltoa(n);
	ft_send_str(buffer, bd, n_str);
	free(n_str);
}

void	ft_send_uint(char *buffer, t_bd *bd, unsigned int n)
{
	char	*n_str;

	n_str = ft_uitoa(n);
	ft_send_str(buffer, bd, n_str);
	free(n_str);
}
