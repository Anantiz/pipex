/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 22:48:51 by aurban            #+#    #+#             */
/*   Updated: 2023/12/02 23:54:29 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
Open pipe --> Fork --> dup(pipes) --> execve()
*/
int	pipex_start(char ***commands, char **envp)
{
	int		child_to_daddy[2];
	int		daddy_to_child[2];
	char	*buffer; // Bufferize strems in-between pipes
	pid_t	pid;
	size_t	i;
	
	/* 0 == read	1 == write */
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
	/* TO DO: write in-file to buffer*/
	i = 1; // commands[0] is in-file
	while (commands[i] && commands[i + 1])
	{
		pid = fork();
		if (pid == -1)	
		{
			perror("Failed to fork");
			exit_clean(commands, EXIT_FAILURE);
		}
		if (pid == 0) // Child
		{
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
			close(child_to_daddy[0]);
			harras_child(buffer, daddy_to_child[1]); // Writes to child stdin
			child_talks_back(buffer, daddy_to_child[0]); // Reads child stdout | How insolent !
		}
		i++;
	}
	/* TO DO : writes buffer to commands[last] a.k.a out-file*/
	return (0);
}
