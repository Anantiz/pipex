/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 19:31:52 by aurban            #+#    #+#             */
/*   Updated: 2023/12/06 12:42:40 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	line_is_eof(char *line, char *eof)
{
	int		cmp;
	size_t	len;

	len = ft_strlen(eof);
	if (len != ft_strlen(eof))
		return (0);
	cmp = ft_strncmp(line, eof, len);
	if (!cmp)
		return (1);
	else
		return (0);
}
/*return -1 on error , returns 1 on eof */
static int	ppp_fb_2(char ***commands, char **buffer, char *line, size_t i)
{
	char	*old_buffer;

	if (line && !line_is_eof(line, *commands[i + 1]))
	{
		old_buffer = *buffer;
		*buffer = ft_strjoin_n(*buffer, line);
		free(old_buffer);
		if (!(*buffer))
			return (free(line), -1);
	}
	if (!line || line_is_eof(line, *commands[i + 1]))
		return (free(line), 1);
	return (0);
}

static int	pipex_parser_fill_buffer(char ***commands, char **buffer, size_t i)
{
	int		status;
	char	*line;
	
	if (ft_strncmp(*commands[i], "here_doc", 9) == 0)
	{
		while (1)
		{
			ft_printf("here_doc> ");
			line = get_next_line(0, 0);
			status = ppp_fb_2(commands, buffer, line, i);
			if (status == -1)
				return (-1);
			else if (status == 1)
				break ;
			free(line);
		}
		get_next_line(0, 1);
		return (1);
	}	
	if (access(*commands[i], R_OK))
		return (msg_invalid_file(*commands[i], 1));
	*buffer = write_infile_to_buff(*commands[i]);
	return (0);
}

int	validate_args_bonus(char ***commands, char **buffer)
{
	size_t	i;
	int		status;

	if (!commands)
		exit(1);
	i = 0;
	if (!(commands[i]) || !(*(commands[i])) || (*(commands[i]))[0] == '\0')
		return (msg_empty_arg(i, 1));
	status = pipex_parser_fill_buffer(commands, buffer, i);
	if (status == -1)
		return (-1);
	else if (status == 1)
		i++;
	i++;
	while (commands[i] && commands[i + 1])
	{
		if (!(*(commands[i])) || (*(commands[i]))[0] == '\0')
			return (msg_empty_arg(i, 1));
		i++;
	}
	return (0);
}
