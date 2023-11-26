/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_send_to_buff.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 02:27:45 by aurban            #+#    #+#             */
/*   Updated: 2023/10/29 02:59:12 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_arg_to_buff3(char *buff, t_bd *bd, va_list *args, char c)
{
	unsigned int	un;
	char			*str;
	long			l;

	if (c == 'X')
	{
		un = va_arg(*args, unsigned int);
		str = ft_uitohex_up(un);
		ft_send_str(buff, bd, str);
		free(str);
	}
	else if (c == '%')
		ft_send_char(buff, bd, '%');
	else if (c == 'l')
	{
		l = va_arg(*args, long);
		ft_send_decimal(buff, bd, l);
	}
	else
		return (-1);
	return (0);
}

static int	ft_arg_to_buff2(char *buff, t_bd *bd, va_list *args, char c)
{
	unsigned int	un;
	int				n;
	char			*str;

	if (c == 'i' || c == 'd')
	{	
		n = va_arg(*args, int);
		ft_send_decimal(buff, bd, n);
	}
	else if (c == 'u')
	{	
		un = va_arg(*args, int);
		ft_send_uint(buff, bd, un);
	}
	else if (c == 'x')
	{
		un = va_arg(*args, unsigned int);
		str = ft_uitohex(un);
		ft_send_str(buff, bd, str);
		free(str);
	}
	else
		return (ft_arg_to_buff3(buff, bd, args, c));
	return (0);
}

/*
This atrocity uses if statments because switch are apparently 
to cool to be used		:(			*sobbing noises*
*/
int	ft_arg_to_buffer(char *buff, t_bd *bd, va_list *args, char c)
{
	void	*p;
	char	*ch;
	int		chr;

	if (c == 'c')
	{
		chr = va_arg(*args, int);
		ft_send_char(buff, bd, (char) chr);
	}
	else if (c == 's')
	{
		ch = va_arg(*args, char *);
		ft_send_str(buff, bd, ch);
	}
	else if (c == 'p')
	{
		p = va_arg(*args, void *);
		ft_send_ptr(buff, bd, p);
	}
	else
		return (ft_arg_to_buff2(buff, bd, args, c));
	return (0);
}
