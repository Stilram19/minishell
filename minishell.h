/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:49:24 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/11 17:17:30 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "defined_types.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>

# define CMN_NF "\e[1;31mMinishell\e[0m: Command not found\n"
# define HD_MSG "here_doc> "

typedef struct s_cmds t_cmds;

enum gar_col
{
	ALLOCATE,
	SINGLE_RELEASE
};

enum token
{
	HD_TOKEN,
	I_REDCT,
	O_REDCT
};

typedef struct s_redc
{
	int	dup_in;
	int	dup_out;
	int	fdout;
	int	fdin;
	int	fds[2];
}	t_redc;

typedef struct s_cmds
{
	int		fdin;
	int		fdout;
	int		ncmds;
	int		id;
	int		token;
	char	*delimiter;
	char	*cmd;
	char	**args;
	t_cmds	*next;
}	t_cmds;

/*Parsing*/
char	**get_env(char **env);
char	**env_dup(char **env);
char	*get_env_var(char *key);
void	set_env(char **my_env, char *name, char *value);
void	*ft_garbage_collector(int option, int size, void *to_free);

/*Execution*/
int		ft_execvp(char *file, char **args);
void	_ft_putstr_fd(char *str, int fd, int ext);
int		is_buildin(char *cmd);
int		ft_strcmp(char *str1, char *str2);

#endif