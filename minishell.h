/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:49:24 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/22 20:35:21 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "defined_types.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include <readline/readline.h>
# include "execution/build-ins/buildins.h"

# define CMN_NF "\e[1;31mMinishell\e[0m: Command not found\n"
# define HD_MSG "here_doc> "

// typedef struct s_cmds t_cmds;
typedef struct s_tree t_tree;

enum gar_col
{
	ALLOCATE,
	SINGLE_RELEASE
};

enum file_type
{
	IN_FILE,
	OUT_FILE,
	HEREDOC,
	APPEND,
	AMBIG
};

enum	e_item_type
{
	L_PARENTH, R_PARENTH, OR, AND, PIPE, OPERAND
};

typedef struct	s_files
{
	char	*name;
	int		type;
	int		fd; // ? in case of heredoc
}	t_files;

typedef struct	s_operand
{
	char	*cmd;
	char	**args;
	t_files	**files;
}	t_operand;

typedef struct	s_item
{
	int			type;
	t_operand	*operand;
}	t_item;

typedef struct	s_tree
{
	// ! required data
	t_item	*item;
	// ! pointers to childs
	t_tree		*left;
	t_tree		*right;
}	t_tree;


/*Binary Tree*/
t_tree	*new_node(int op_type, t_operand *cmds);

/*Parsing*/
char	**get_env(char **env);
char	**env_dup(char **env);
char	*get_var_value(char *key);
int		envlen(char **env);
void	set_env(char **my_env, char *name, char *value);
void	*ft_garbage_collector(int option, int size, void *to_free);

/*Execution*/
int		execute(t_tree *root, int in, int out);
int		ft_execvp(char *file, char **args);
void	_ft_putstr_fd(char *str, int fd, int ext);
int		is_buildin(char *cmd);
int		ft_strcmp(char *str1, char *str2);
int		redirect_io(t_operand *cmds, int in, int out);
int		redirect_error(int error_key, int ext);
void	ft_dup2(int f1, int f2);
void	set_exit_status(int status);

/*UTILS*/
t_operand	*command_fill(char *cmd, int fd_in, int fd_out);

t_list *matched_set(char *pattern);

#endif