/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 22:48:51 by aurban            #+#    #+#             */
/*   Updated: 2023/12/06 12:49:28 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*
	dup2(sd->daddy[0], 0); // Parent writes to childs stdin
	dup2(sd->child[1], 1); // Redirect child stdout to parent
*/
static void	pipex_fork_child(t_sdata *sd, char **envp)
{
	size_t	i;
	size_t	j;

	i = sd->i;
	if (dup2(sd->daddy[0], 0) == -1 || dup2(sd->child[1], 1) == -1)
	{
		perror("dup2() error in fork child");
		exit_clean(sd, EXIT_FAILURE);
	}
	close(sd->child[0]);
	close(sd->child[1]);
	close(sd->daddy[0]);
	close(sd->daddy[1]);
	j = 0;
	while (sd->cmds_paths[i - 1][j])
	{
		execve(sd->cmds_paths[i - 1][j], sd->cmds_files[i], envp);
		j++;
	}
	ft_printf_fd(2, "\"%s\" ", sd->cmds_files[i][0]);
	perror("command not found");
	exit_clean(sd, EXIT_FAILURE);
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
		exit_clean(sd, EXIT_FAILURE);
	}
	if (pipe(sd->daddy))
	{
		perror("Pipe: Daddy_to_child failed");
		exit_clean(sd, EXIT_FAILURE);
	}
}

static void	pipex_loop(t_sdata *sd, char **envp, char **buffer)
{
	pipex_loop_get_pipe(sd);
	sd->pid = fork();
	if (sd->pid == -1)
	{
		perror("Failed to fork");
		exit_clean(sd, EXIT_FAILURE);
	}
	if (sd->pid == 0)
		pipex_fork_child(sd, envp);
	else
		*buffer = pipex_fork_parent(sd, *buffer);
	sd->i++;
}

int	pipex_start_bonus(char ***cmds_files, int argc, char **envp, char *buffer)
{
	int		daddy[2];
	int		child[2];
	t_sdata	sd;
	int		append;

	sd = (t_sdata){daddy, child, cmds_files, NULL, 0, 0, 0};
	sd.i = 1;
	append = 0;
	if (ft_strncmp(cmds_files[0][0], "here_doc", 9) == 0)
	{
		sd.i++;
		argc--;
		append = 1;
	}
	sd.cmds_paths = get_commands_paths(argc - 1, cmds_files, envp);
	if (!sd.cmds_paths)
	{
		free(buffer);
		exit_clean(&sd, EXIT_FAILURE);
	}
	while (cmds_files[sd.i] && cmds_files[sd.i + 1])
		pipex_loop(&sd, envp, &buffer);
	free_triple_char(sd.cmds_paths);
	write_buff_to_outfile(cmds_files[sd.i][0], buffer, append);
	return (free(buffer), 0);
}
