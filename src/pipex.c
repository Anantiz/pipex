/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 22:48:51 by aurban            #+#    #+#             */
/*   Updated: 2023/12/03 04:12:13 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>

/*
Open pipe --> Fork --> dup(pipes) --> execve()
*/
int	pipex_start(char ***commands, char **envp)
{
	int		child_to_daddy[2];
	int		daddy_to_child[2];
	int		wstatus;
	char	*buffer; // Bufferize streams in-between pipes
	pid_t	pid;
	size_t	i;
	
	/* 0 == read	1 == write */
	buffer = write_infile_to_buff(commands[0][0]);
	if (!buffer)
	{
		ft_printf_fd(2, "Failed to read in-file\n");
		exit_clean(commands, EXIT_FAILURE);
	}
	i = 1; // commands[0] is in-file
	printf("BUFF in_file: %s||\n", buffer);
	while (commands[i] && commands[i + 1])
	{
		if (pipe(child_to_daddy))
		{
			perror("Pipe: Child_to_daddy failed");
			exit_clean(commands, EXIT_FAILURE);
		}
		if (pipe(daddy_to_child))
		{
			perror("Pipe: Daddy_to_child failed");
			exit_clean(commands, EXIT_FAILURE);
		}
		printf("Cmd:  %s\n",commands[i][0]);
		pid = fork();
		if (pid == -1)	
		{
			perror("Failed to fork");
			exit_clean(commands, EXIT_FAILURE);
		}
		if (pid == 0) // Child
		{
			// You might WANT TO SECURE dup2()
			dup2(daddy_to_child[0], 0); // Parent writes to childs stdin
			dup2(child_to_daddy[1], 1); // Redirect child stdout to parent
			close(child_to_daddy[0]);
			close(child_to_daddy[1]);
			close(daddy_to_child[0]);
			close(daddy_to_child[1]);
			if (execve(commands[i][0], commands[i], envp) == -1)
			{
				ft_printf_fd(2, "Command \"%s\"\n", commands[i][0]);
				perror("FAILURE");
				exit_clean(commands, EXIT_FAILURE);
			}
		}
		else
		{
			close(daddy_to_child[0]);
			close(child_to_daddy[1]);
			// Writes to child stdin
			write_buffer_to_child(buffer, daddy_to_child[1]);
			close(daddy_to_child[1]);
			waitpid(pid, &wstatus, WEXITSTATUS(0));
			// Reads child stdout
			buffer = write_child_to_buffer(buffer, child_to_daddy[0]);
			close(child_to_daddy[0]);
		}
		i++;
		printf("BUFF: %s||\n", buffer);
	}
	write_buff_to_outfile(commands[i][0], buffer);
	free(buffer);
	return (0);
}
