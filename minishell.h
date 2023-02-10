/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:49:24 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/10 15:42:25 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "defined_types.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_cmds t_cmds;

enum gar_col
{
	ALLOCATE,
	SINGLE_RELEASE
};

typedef struct s_redc
{
	int	tmpin;
	int	tmpout;
	int	fdout;
	int	fdin;
	int	fds[2];
}	t_redc;

typedef struct s_cmds
{
	char	*cmd;
	char	**args;
	int		fdin;
	int		fdout;
	t_cmds	*next;
}	t_cmds;

char	**get_env(char **env);
char	**env_dup(char **env);
char	*get_env_var(char *key);
void	set_env(char **my_env, char *name, char *value);
void	*ft_garbage_collector(int option, int size, void *to_free);

#endif