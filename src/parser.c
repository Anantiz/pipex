/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 19:31:52 by aurban            #+#    #+#             */
/*   Updated: 2023/12/05 17:32:43 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

char	**parser_get_item(char **argv, size_t i)
{
	char	**item;

	if (!argv[i])
		return (NULL);
	item = ft_calloc(2, sizeof(char *));
	if (!item)
		return (NULL);
	item[0] = ft_strdup(argv[i]);
	return (item);
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
	commands[i] = parser_get_item(argv, i);
	if (!commands[i])
		return (free_triple_char(commands));
	i++;
	while (argv[i] && argv[i + 1])
	{
		command = ft_split(argv[i], ' ');
		if (!command)
			return (free_triple_char(commands));
		commands[i++] = command;
	}
	commands[i] = parser_get_item(argv, i);
	if (!commands[i])
		return (free_triple_char(commands));
	return (commands);
}

int	validate_args(char ***commands)
{
	size_t	i;

	if (!commands)
	{
		ft_printf("Memory error while parsing arguments\n");
		exit(0);
	}
	i = 0;
	if (!(commands[i]) || !(*(commands[i])) || (*(commands[i]))[0] == '\0')
		return (msg_empty_arg(i, 1));
	if (access(*commands[i], R_OK))
		return (msg_invalid_file(*commands[i], 1));
	i++;
	while (commands[i] && commands[i + 1])
	{
		if (!(*(commands[i])) || (*(commands[i]))[0] == '\0')
			return (msg_empty_arg(i, 1));
		i++;
	}
	return (0);
}
