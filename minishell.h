/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:49:24 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/28 18:20:18 by obednaou         ###   ########.fr       */
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
# include "defined_types.h"
# include "readline/readline.h"

void	sig_set(void);
void	sig_def(void);
int		is_blank(char c);
void	heredoc_sig(void);
int		var_name_len(char *var);
int		is_redirect(char *c);
char	**get_env(char **env);
char	**env_dup(char **env);
char	*get_var_value(char *key);
void	expand_if(char **ptr_to_token);
char	*remove_quotes(char *token);
char	*left_str(char *str, char *op);
char	*random_file_name_generation(void);
char	*right_str(char *str, char *op, int with_op);
void	set_env(char **my_env, char *name, char *value);
void	*ft_garbage_collector(int option, int size, void *to_free);
char	*var_expansion(char **ptr_to_token, int *ptr_to_i, int name_len);
char	**produce_tokens(char *line, char *mask);
char	*mask_generation1(char *line);
char	*mask_generation(char *line);
int		check_syntax(char **tokens);
int		first_production_rule(char *str);
int		third_production_rule(char *str);
int		fourth_production_rule(char *str);
void	open_close_quotes(char ch, int *c);
void	open_close_parenth(char ch, int *c);
void	heredoc_sig_handler(int sig);
char	*unmask_quotes(char *str);
char	*first_operand(char *str);
char	*second_operand(char *str);
char	*remove_outer_parenth(char *str);
int		is_between_parenth(char *str);
int		check_command_syntax(char *str);
int		is_there_middle_operator(char *str);
void	queue_push(t_queue *q, void *data);
int		add_history(const char *);
void	*queue_first(t_queue *q);
void	*queue_pop(t_queue *q);
void	heredoc_clean(void);
void	queue_init(t_queue *q);
void	open_heredoc(char **tokens, int fd);
void	cmd_parsing(t_node *root, char *str);
void	files_parsing(t_node *root, char *str);
t_file	*get_here_doc(t_file *files, int len);

#endif
