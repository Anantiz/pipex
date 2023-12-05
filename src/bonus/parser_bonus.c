/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 19:31:52 by aurban            #+#    #+#             */
/*   Updated: 2023/12/05 15:56:26 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	***free_triple_char(char ***ccc)
{
	size_t	i;
	size_t	j;

	if (!ccc)
		return (NULL);
	i = 0;
	while (ccc[i])
	{
		j = 0;
		while (ccc[i][j])
			free(ccc[i][j++]);
		free(ccc[i++]);
	}
	free(ccc);
	return (NULL);
}

char	**free_double_char(char **cc)
{
	size_t	i;

	if (!cc)
		return (NULL);
	i = 0;
	while (cc[i])
		free(cc[i++]);
	free(cc);
	return (NULL);
}

char	***args_parser(int argc, char **argv)
{
	char	***commands;
	char	**command;
	size_t	i;

	if (!argv || !argc)
		return (NULL);
	commands = ft_calloc(argc, sizeof(char ***));
	if (!commands)
		return (NULL);
	i = 0;
	while (argv[i])
	{
		command = ft_split(argv[i], ' ');
		if (!command)
			return (free_triple_char(commands));
		commands[i++] = command;
	}
	return (commands);
}

int	validate_args(char ***commands, char **buffer)
{
	size_t	i;
	char	*line;
	char	*old_buffer;

	if (!commands)
		exit(1);
	i = 0;
	if (!(commands[i]) || !(*(commands[i])) || (*(commands[i]))[0] == '\0')
		return (msg_empty_arg(i, 1));

/////////////////////////////////////

	// here_doc handling
	ft_printf("first arg: %s\n", *commands[i]);
	if (ft_strncmp(*commands[i], "here_doc", 9) == 0)
	{
		while (1)
		{
			ft_printf("here_doc> ");
			line = get_next_line(0, 0);
			if (line && ft_strncmp(line, *commands[i + 1], ft_strlen(*commands[i + 1] + 1)) != 0)
			{
				old_buffer = *buffer;
				*buffer = ft_strjoin(*buffer, line);
				free(old_buffer);
				if (!(*buffer))
					return (free(line), 1);
			}
			free(line);
			if (!line || ft_strncmp(line, *commands[i + 1], ft_strlen(*commands[i + 1] + 1)) == 0)
				break ;
		}
		get_next_line(0, 1);
		i++;
	}	
	else // Normal file handling
	{
		if (access(*commands[i], R_OK))
			return (msg_invalid_file(*commands[i], 1));
		*buffer = write_infile_to_buff(*commands[i]);
	}


////////////////////////////////////////////

	i++;
	while (commands[i] && commands[i + 1])
	{
		if (!(*(commands[i])) || (*(commands[i]))[0] == '\0')
			return (msg_empty_arg(i, 1));
		i++;
	}
	return (0);
}
