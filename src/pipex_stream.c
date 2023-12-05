/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_stream.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 13:50:32 by aurban            #+#    #+#             */
/*   Updated: 2023/12/05 16:00:28 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	free_pipes(int **pipes, int i)
// {
// 	if (!pipes)
// 		return ;
// 	while (i > 0)
// 		free(pipes[i--]);
// 	free(pipes);
// 	return ;
// }

// int	**init_pipes_stream(int cmd_count)
// {
// 	int	**pipes;
// 	int	i;

// 	pipes = malloc((cmd_count + 1) * sizeof(int *));
// 	if (!pipes)
// 		return (NULL);
// 	i = 0;
// 	while (i <= cmd_count)
// 	{
// 		pipes[i] = malloc(2 * sizeof(int));
// 		if (!pipes[i])
// 			return (free_pipes(pipes, i), NULL);
// 		if (pipe(pipes[i]))
// 		{
// 			perror("Pipe: creation error");
// 			return (free_pipes(pipes, i), NULL);
// 		}
// 		i++;
// 	}
// 	return (pipes);
// }

static size_t	cc_lst_size(char **cc)
{
	size_t	i;

	i = 0;
	while (cc[i])
		i++;
	return (i);
}

static char	**clear_path(int i, int path_size, char **paths)
{
	paths[i] = NULL;	
	while (path_size > 0)	
		if (paths[path_size--] != NULL)	
			free(paths[path_size + 1]);	
	return (NULL);
}

static char	**get_envp_path(char **envp)
{
	int		i;
	char	**paths;
	int		path_size;

	path_size = 0;
	while (ft_strncmp(envp[path_size], "PATH=", 5) != 0)
		path_size++;
	paths = ft_split(envp[path_size], ':');
	if (!paths || !paths[0])
		return (NULL);
	path_size = cc_lst_size(paths);
	i = 0;
	while (paths[i])
	{
		paths[i] = resize_line(paths[i], 1);
		if (!paths[i])
			return (clear_path(i, path_size, paths));
		paths[i][ft_strlen(paths[i])] = '/';
		i++;
	}
	return (paths);
}

static char	**getpaths2(char **p, char ***cmds, size_t i)
{
	size_t	j;
	char	**cmd_paths;

	cmd_paths = ft_calloc(cc_lst_size(p) + 1, sizeof (char *));
	j = 0;
	if (!cmd_paths)
		return (free_double_char(p));
	while (p[j])
	{
		
		cmd_paths[j] = ft_strjoin(p[j], cmds[i][0]);
		if (!cmd_paths[j])
			return (free_double_char(p));
		j++;
	}
	return (cmd_paths);
}

char	***get_commands_paths(int argc, char ***cmds, char **envp)
{
	int		i;
	char	**envp_paths;
	char	***cmds_paths;

	envp_paths = get_envp_path(envp);
	if (!envp_paths)
		return (NULL);
	cmds_paths = ft_calloc(argc, sizeof(char **)); // Make list of list of path
	if (!cmds_paths)
		return (NULL);
	i = 1;
	while (i < argc)
	{
		cmds_paths[i - 1] = getpaths2(envp_paths, cmds, i);
		if (!cmds_paths[i - 1])
			return (free_triple_char(cmds_paths));
		i++;
	}
	free_double_char(envp_paths);
	return (cmds_paths);
}
