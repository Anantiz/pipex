/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 19:34:08 by aurban            #+#    #+#             */
/*   Updated: 2023/12/05 15:39:00 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft.h"
# include "pipex.h"

int	validate_args_bonus(char ***commands, char **buffer);
int	pipex_start_bonus(char ***commands, int argc, char **envp, char *buffer);

#endif