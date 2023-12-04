/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_stream.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 13:50:32 by aurban            #+#    #+#             */
/*   Updated: 2023/12/04 18:20:37 by aurban           ###   ########.fr       */
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

static char	**get_envp_path(char **envp)
{
	int	i;

	i = 0;
	while (!ft_strncmp(envp[i], "PATH", 4))
		i++;
	return (ft_split(envp[i], ':'));
}

char	***get_commands_path(int argc, char ***cmds, char **envp)
{
	size_t	i;
	size_t	j;
	char	**envp_paths;
	char	***cmds_paths
	
	cmds_paths = ft_calloc(argc - 2, sizeof(char **)); // Make list of list of path
	if (!cmds_paths)
		return (NULL);
	i = 1;
	envp_paths = get_envp_path(envp);
	while (cmds[i] && cmds[i + 1]) //for each cmd
	{
		j = 0;
		while (envp_paths[j]) // For each path in envp.PATH
		{
			cmd_path = ft_strjoin(envp_paths[j], cmds[i][0]);//handle error
			if (!cmd_path)
			{
				j = 0;
				while (envp_paths + j)
					free(envp_paths + (j++))
				free_triple_char(cmds_paths);
				return (NULL);
			}
			cmds_paths[i - 1][j] = cmd_path;
			j++;
		}
		i++;
	}
	j = 0;
	while (envp_paths + j)
		free(envp_paths + (j++))
	return (cmds_paths);
}


/*
buff

line

line += buff[i]

line "aaa\0\0\0\0\0"

Solution1:
	line = resizeline(line) --> line..."00000000"
Solution 2:

	nread=1
	while(buff[i] ! \n or \0)
		i++
	old line = line
	line = str_join (line, buffer, i)
	if (line[i]) == \n
		return
while (nread != 0)
{
	nread = read()
	if (nread == 0)
		return (NULL)
	while (buffer[i])
	{
		while(buff[i] ! \n or \0)
			i++
	old line = line
	line = str_join (line, buffer, i)
	free old line
	if (line[i]) == \n
		return
	}
}
*/