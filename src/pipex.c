/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 22:48:51 by aurban            #+#    #+#             */
/*   Updated: 2023/12/03 18:14:22 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
	// You might WANT TO SECURE dup2()
	dup2(sd->daddy[0], 0); // Parent writes to childs stdin
	dup2(sd->child[1], 1); // Redirect child stdout to parent
*/
static void	pipex_fork_child(t_sdata *sd, char **envp)
{
	size_t	i;

	i = sd->i;
	dup2(sd->daddy[0], 0);
	dup2(sd->child[1], 1);
	close(sd->child[0]);
	close(sd->child[1]);
	close(sd->daddy[0]);
	close(sd->daddy[1]);
	if (execve(sd->cmds_path[i - 1], sd->cmds_files[i], envp) == -1)
	{
		free(sd->cmds_path[i - 1]);
		sd->cmds_path[i - 1] = NULL;
		if (execve(sd->cmds_files[i][0], sd->cmds_files[i], envp) == -1)
		{
			ft_printf_fd(2, "\"%s\" ", sd->cmds_files[i][0]);
			perror("command not found");
			exit_clean(sd->cmds_files, EXIT_FAILURE);
		}
	}
}

static char	*pipex_fork_parent(t_sdata *sd, char *buffer)
{
	close(sd->daddy[0]);
	close(sd->child[1]);
	write_buffer_to_child(buffer, sd->daddy[1]);
	close(sd->daddy[1]);
	waitpid(sd->pid, &sd->wstatus, WEXITSTATUS(0));
	buffer = write_child_to_buffer(buffer, sd->child[0]);
	close(sd->child[0]);
	return (buffer);
}

/* 0 == read-end	1 == write-end */
static void	pipex_loop_get_pipe(t_sdata *sd)
{
	if (pipe(sd->child))
	{
		perror("Pipe: Child_to_daddy failed");
		exit_clean(sd->cmds_files, EXIT_FAILURE);
	}
	if (pipe(sd->daddy))
	{
		perror("Pipe: Daddy_to_child failed");
		exit_clean(sd->cmds_files, EXIT_FAILURE);
	}
}

static void	pipex_loop(t_sdata *sd, char **envp, char **buffer)
{
	pipex_loop_get_pipe(sd);
	sd->pid = fork();
	if (sd->pid == -1)
	{
		perror("Failed to fork");
		exit_clean(sd->cmds_files, EXIT_FAILURE);
	}
	if (sd->pid == 0)
		pipex_fork_child(sd, envp);
	else
		*buffer = pipex_fork_parent(sd, *buffer);
	sd->i++;
}

int	pipex_start(char ***cmds_files, int argc, char **envp)
{
	int		daddy[2];
	int		child[2];
	char	**cmds_path;
	char	*buffer;
	t_sdata	sd;

	buffer = write_infile_to_buff(cmds_files[0][0]);
	if (!buffer)
		exit_clean(cmds_files, EXIT_FAILURE);
	cmds_path = ft_calloc(argc - 2, sizeof(char *));
	sd = (t_sdata){daddy, child, cmds_files, cmds_path, 0, 0, 0};
	sd.i = 1;
	while (cmds_files[sd.i])
	{
		cmds_path[sd.i - 1] = ft_strjoin("/bin/", cmds_files[sd.i][0]);
		sd.i++;
	}
	sd.i = 1;
	while (cmds_files[sd.i] && cmds_files[sd.i + 1])
		pipex_loop(&sd, envp, &buffer);
	write_buff_to_outfile(cmds_files[sd.i][0], buffer);
	clean_cmd_paths(cmds_path, argc - 2);
	free(buffer);
	return (0);
}
