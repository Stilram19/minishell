/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:49:24 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/09 02:46:03 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <sys/stat.h>
# include <termios.h>
# include "defined_types.h"
# include "readline/readline.h"

void	sig_set(void);
void	sig_def(void);
int		is_blank(char c);
int		is_meta(char *str);
int		is_all_blank(char *file_name);
void	heredoc_sig_handler(int sig);
int		var_name_len(char *var);
int		is_redirect(char *c);
char	**get_env(char **env);
char	**env_dup(char **env);
char	*get_var_value(char *key);
char	*get_prompt(int exit_status);
void	expand_if(char **ptr_to_token);
char	*remove_quotes(char *token);
char	*left_str(char *str, char *op);
char	*join_tokens(char **tokens);
char	*args_files_separation(char *str);
char	*random_file_name_generation(void);
char	*right_str(char *str, char *op, int with_op);
int		is_empty_parenth(char *str);
void	set_env(char **my_env, char *name, char *value);
void	*ft_garbage_collector(int option, int size, void *to_free);
void	ft_heredoc(int fd, t_queue *limiters, int expand);
char	*var_expansion(char **ptr_to_token, int *ptr_to_i, int name_len);
char	**produce_tokens(char *line, char *mask);
char	*ft_strjoin1(char const *s1, char const *s2);
char	*mask_generation3(char *line, char *meta);
char	*mask_generation4(char *line, char *meta);
char	*ft_strdup1(const char *s1);
char	*mask_generation2(char *line);
char	*mask_generation(char *line);
int		syntax_test(char *str);
int		is_ambiguous_redirect(char **ptr_to_file_name);
void	global_init(int argc, char **argv, char **env);
void	open_close_quotes(char ch, int *c);
void	open_close_parenth(char ch, int *c);
void	display_tree(t_node	*root, int indent_level);
void	heredoc_sig_handler(int sig);
char	*unmask_quotes(char *str);
char	*first_operand(char *str);
char	*second_operand(char *str);
char	*remove_outer_parenth(char *str);
char	*remove_outer_parenth2(char *str);
int		is_between_parenth(char *str);
int		check_command_syntax(char *str);
char	*get_operator(char *op);
int		operator_type(char *op);
int		is_there_middle_operator(char *str);
void	queue_push(t_queue *q, void *data);
void	node_init(t_node *root, int status);
int		add_history(const char *str);
void	*queue_first(t_queue *q);
void	ft_free(char **tokens);
void	*queue_pop(t_queue *q);
void	*ft_min(void *add1, void *add2);
char	*get_prompt(int exit_status);
void	heredoc_clean(int status);
int		here_sig(void);
void	refresh(char *line);
void	queue_init(t_queue *q);
void	cmd_parsing(t_node *root, char *str);
void	files_parsing(t_node *root, char *str);
void	parse_tree(char *str, t_node *root, int status);
t_file	*get_here_doc(t_file *files, int len);
t_queue	*get_limiters(char **tokens, int *expand_enable);
int		envlen(char **env);

/*Execution*/
int		execution(t_node *root);
int		check_subshell(t_node *root, t_fdio in, t_fdio out, int level);
int		execute(t_node *root, t_fdio in, t_fdio out);
int		exec_cmds(t_data *cmds, t_fdio in, t_fdio out);
int		buildins_brute_force(t_data *cmds, int flag);
int		exec_buildin(t_data *cmds, t_fdio in, t_fdio out);
int		ft_execvp(char *file, char **args);
void	_ft_putstr_fd(char *str, int fd, int ext);
int		is_buildin(char *cmd);
int		ft_strcmp(char *s1, char *s2);
t_fdio	*io_rect(t_data *data, t_fdio in, t_fdio out);
int		is_directory(char *path);
void	set_exit_status(int status);
char	**_ft_split(char const *str, char c);
int		io_subs_type(t_fdio *in, t_fdio *out);
char	*search_replace(char *str, char needle, char replecement);
t_list	*matched_set(char *pattern);
char	**wildcards_slice(char **args);
void	ft_dup2(int f1, int f2);
void	error_msg(char *msg);
void	check_fail_reason(int fail, char *file);
int		defaults_io(int in_type, int out_type);
int		check_exit_reason(int status);
int		is_signaled(int status);
t_fdio	*set_io_type(int *fds, int type);
t_fdio	*init_fdio(t_fdio in, t_fdio out);
void	clean_up_of(int *io);
void	open_file_error(char *file);
int		ft_cd(char **args);
int		ft_pwd(void);
int		ft_env(void);
int		ft_exit(char **args, int flag);
int		ft_echo(char **args);
int		ft_unset(char **args);
int		ft_export(char **args);
int		name_len(char *name, int *append);
int		valid_arg(char *arg, int *append);
int		is_exist(char **env, char *identifier);
void	ft_set_var(char **env, char *var, int append);

#endif
