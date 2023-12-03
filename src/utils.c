/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 21:37:14 by aurban            #+#    #+#             */
/*   Updated: 2023/12/03 17:26:26 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_clean(char ***ccc, int status)
{
	free_triple_char(ccc);
	exit(status);
}

int	msg_invalid_cmd(char *s, int r)
{
	ft_printf("Command does not exist: \"%s\"\n", s);
	return (r);
}

int	msg_denied_cmd(char *s, int r)
{
	ft_printf("Acces to command denied: \"%s\"\n", s);
	return (r);
}

int	msg_invalid_file(char *s, int r)
{
	ft_printf("Invalid file\n\tFile does not exist or "
		"premission denied: \"%s\"\n", s);
	return (r);
}

int	msg_empty_arg(int pos, int r)
{
	ft_printf("Invalid input\n\tPositional argument '%d' is empty\n", pos);
	return (r);
}
