/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:15:51 by aurban            #+#    #+#             */
/*   Updated: 2023/12/02 23:35:35 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*

GLOBAL IDEA:

	For first command
		args += in-File
  ->We want for each commands to:
 /		1.Create a pipe
 |		2.Fork the process
 ----->	3.Redirect(dup2()) the child-process stdout into a """desired location"""
/		  The child process "ls" for example would be working with stdin
|	Redirect last command output to out-File
|
|	
\
 --> How to execute all commands ?
	e.i: in_file -> cmd1 -> cmd2 -> cmd3 -> out_file
	Itterative:
		read(in_file, buffer)
		loop(cmd)
		{
			pipe(parent_to_child)
			pipe(child_to_parent)
			fork()
			child:
				dup2(parent_to_child_in, stdin)
				dup2(stdout, child_to_parent_out)
				execv(cmd, cmd_args)
			parent:
				write(parent_to_child_out, buffer) // writes in the execv stdin the last command input from the buffer
				waitpid(child)
				read (child_to_parent_inm, buffer) -> write it in some buffer for stdin of next cmd
		}
		write(out_file, buffer)
	NO RECURSIVE, Large pipes will Kill the CPU
	First and Last argument are files
	All others are commands
PARSE ARGUMENTS
	execv(args[0], args);
STDIN_FILENO
*/
static int	msg_wrong_use(int r)
{
	ft_printf("Wrong usage\n\t"
	"pipex takes 4 arguments as input\n\t"
	"$>infile \"cmd1\" \"cmd2\" outfile\n");
	return (r);
}

int	main(int argc, char **argv, char **envp)
{
	char	***commands;

	if (argc == 1)
		return (0);
	if (argc != 5)
		return (msg_wrong_use(0));
	commands = args_parser(argc, argv + 1);
	if (validate_args(commands))
		exit_clean(commands, EXIT_FAILURE);
	pipex_start(commands, envp);
	free_triple_char(commands);
	return (0);
}