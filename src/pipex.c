/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 22:48:51 by aurban            #+#    #+#             */
/*   Updated: 2023/12/03 17:36:03 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex_start(char ***commands_and_files, int argc, char **envp)
{
	int		child_to_daddy[2];
	int		daddy_to_child[2];
	char	**commands_path;
	int		wstatus;
	char	*buffer; // Bufferize streams in-between pipes
	pid_t	pid;
	size_t	i;
	
	/* 0 == read-end	1 == write-end */
	buffer = write_infile_to_buff(commands_and_files[0][0]);
	if (!buffer)
		exit_clean(commands_and_files, EXIT_FAILURE);
	commands_path = ft_calloc(argc - 2, sizeof(char *));
	i = 1;
	while (commands_and_files[i])
	{
		commands_path[i - 1] = ft_strjoin("/bin/", commands_and_files[i][0]);
		i++;
	}
	i = 1;
	while (commands_and_files[i] && commands_and_files[i + 1])
	{
		if (pipe(child_to_daddy))
		{
			perror("Pipe: Child_to_daddy failed");
			exit_clean(commands_and_files, EXIT_FAILURE);
		}
		if (pipe(daddy_to_child))
		{
			perror("Pipe: Daddy_to_child failed");
			exit_clean(commands_and_files, EXIT_FAILURE);
		}
		// printf("Cmd:  %s\n",commands_and_files[i][0]);
		pid = fork();
		if (pid == -1)	
		{
			perror("Failed to fork");
			exit_clean(commands_and_files, EXIT_FAILURE);
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
			if (execve(commands_path[i - 1], commands_and_files[i], envp) == -1)
			{
				free(commands_path[i - 1]);
				if (execve(commands_and_files[i][0], commands_and_files[i], envp) == -1)
				{
					ft_printf_fd(2, "\"%s\" ", commands_and_files[i][0]);
					perror("command not found");
					exit_clean(commands_and_files, EXIT_FAILURE);
				}
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
	}
	write_buff_to_outfile(commands_and_files[i][0], buffer);
	free(buffer);
	return (0);
}
