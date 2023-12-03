/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_stream.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 13:50:32 by aurban            #+#    #+#             */
/*   Updated: 2023/12/03 15:48:35 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_pipes(int **pipes, int i)
{
	if (!pipes)
		return ;
	while (i > 0)
		free(pipes[i--]);
	free(pipes);
	return ;
}

int	**init_pipes_stream(int cmd_count)
{
	int	**pipes;
	int	i;

	pipes = malloc((cmd_count + 1) * sizeof(int *));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i <= cmd_count)
	{
		pipes[i] = malloc(2 * sizeof(int));
		if (!pipes[i])
			return (free_pipes(pipes, i), NULL);
		if (pipe(pipes[i]))
		{
			perror("Pipe: creation error");
			return (free_pipes(pipes, i), NULL);
		}
		i++;
	}
	return (pipes);
}
