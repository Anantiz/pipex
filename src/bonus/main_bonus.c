/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:15:51 by aurban            #+#    #+#             */
/*   Updated: 2023/12/06 14:21:28 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	msg_wrong_use(int r)
{
	ft_printf("Wrong usage\n\t"
		"pipex takes 4+ arguments as follow\n\t"
		"  $>infile \"cmd1\" \"cmd2\" \"...\" outfile\n"
		"\tOr 5+ arguments as follow\n"
		"\t  $>here_doc [EOF] \"cmd1\" \"cmd2\" \"...\" outfile\n");
	return (r);
}

int	main(int argc, char **argv, char **envp)
{
	char	***commands;
	char	*buffer;

	if (argc == 1)
		return (0);
	if (argc < 5 || (argc < 6 && ft_strncmp(argv[1], "here_doc", 9) == 0))
		return (msg_wrong_use(0));
	commands = args_parser_bonus(argc, argv + 1);
	buffer = NULL;
	if (validate_args_bonus(commands, &buffer))
	{
		ft_printf_fd(2, "Args parsing failed\n");
		free(buffer);
		return (free_triple_char(commands) != NULL);
	}
	pipex_start_bonus(commands, argc, envp, buffer);
	free_triple_char(commands);
	return (0);
}
