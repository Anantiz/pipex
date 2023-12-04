/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 19:34:08 by aurban            #+#    #+#             */
/*   Updated: 2023/12/04 17:26:29 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
#include <stdio.h>

typedef struct s_stream_data
{
	int		*daddy;
	int		*child;
	char	***cmds_files;
	char	***cmds_paths;
	size_t	i;
	pid_t	pid;
	int		wstatus;
}t_sdata;

/* PARSING */
char		***args_parser(int argc, char **argv);
char		***free_triple_char(char ***ccc);
int			validate_args(char ***commands);

/* CORE */

int			pipex_start(char ***commands, int argc, char **envp);
// int		**init_pipes_stream(int cmd_count);
// void		free_pipes(int **pipes, int i);

/*
DATA-STREAMS ------------------------------------------------------------------
*/

char		*ft_read_fd(int fd);
ssize_t		ft_write_fd(int fd, char *content);
ssize_t		write_buffer_to_child(char *buff, int fd);
char		*write_child_to_buffer(char *buff, int fd);
ssize_t		write_buff_to_outfile(char *outfile_path, char *buffer);
char		*write_infile_to_buff(char *infile);

/*
UTILS
*/

void		exit_clean(char ***ccc, int status);
void		clean_cmd_paths(char **cmds_path, int size);
int			msg_invalid_cmd(char *s, int r);
int			msg_denied_cmd(char *s, int r);
int			msg_invalid_file(char *s, int r);
int			msg_empty_arg(int pos, int r);

#endif