/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:15:51 by aurban            #+#    #+#             */
/*   Updated: 2023/12/04 18:02:26 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// static int	msg_wrong_use(int r)
// {
// 	ft_printf("Wrong usage\n\t"
// 		"pipex takes 4 arguments as input\n\t"
// 		"$>infile \"cmd1\" \"cmd2\" outfile\n");
// 	return (r);
// }

int	main(int argc, char **argv, char **envp)
{
	char	***commands;

	// for (int x=0; envp[x];x++)
	// 	printf("%s\n", envp[x]);

	if (argc == 1)
		return (0);
	if (argc < 5)
		return (msg_wrong_use(0));
	commands = args_parser(argc, argv + 1);
	if (validate_args(commands))
		exit_clean(commands, EXIT_FAILURE);
	pipex_start(commands, argc, envp);
	free_triple_char(commands);
	return (0);
}
