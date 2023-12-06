/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:34:53 by aurban            #+#    #+#             */
/*   Updated: 2023/12/06 14:20:50 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	args_parser_bonus2(char **argv, char ***commands, size_t *i)
{
	if (ft_strncmp(commands[0][0], "here_doc", 9) == 0)
	{
		commands[1] = parser_get_item(argv, 1);
		if (!commands[1])
			return (-1);
		(*i)++;
	}
	return (0);
}

char	***args_parser_bonus(int argc, char **argv)
{
	char	***commands;
	char	**command;
	size_t	i;

	commands = ft_calloc(argc, sizeof(char ***));
	if (!commands)
		return (NULL);
	i = 0;
	commands[0] = parser_get_item(argv, 0);
	if (!commands[0])
		return (free_triple_char(commands));
	if (args_parser_bonus2(argv, commands, &i))
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
