/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 19:34:08 by aurban            #+#    #+#             */
/*   Updated: 2023/12/02 23:40:41 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <errno.h>
# include <sys/types.h>
#include <stdio.h>

/* PARSING */
char		***args_parser(int argc, char **argv);
char		***free_triple_char(char ***ccc);
int			validate_args(char ***commands);

/* CORE */

int			pipex_start(char ***commands, char **envp);

/*
UTILS
*/

void		exit_clean(char ***ccc, int status);
int			msg_invalid_cmd(char *s, int r);
int			msg_denied_cmd(char *s, int r);
int			msg_invalid_file(char *s, int r);
int			msg_empty_arg(int pos, int r);

#endif