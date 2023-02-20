/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:49:24 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/20 12:57:11 by obednaou         ###   ########.fr       */
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
int		var_name_len(char *var);
int		is_redirect(char *c);
char	**get_env(char **env);
char	**env_dup(char **env);
char	*get_var_value(char *key);
void	expanding(char **tokens);
char	*remove_quotes(char *token);
void	set_env(char **my_env, char *name, char *value);
void	*ft_garbage_collector(int option, int size, void *to_free);
char	*var_expansion(char **ptr_to_token, int *ptr_to_i, int name_len);
char	**produce_tokens(char *line, char *mask);
char	*mask_generation(char *line);
int		check_syntax(char **tokens);
int		first_production_rule(char *str);
int		third_production_rule(char *str);
int		fourth_production_rule(char *str);
void	update_balance(char c, t_balance *b);
void	open_close_quotes(char ch, int *c);
char	*first_operand(char *str);
char	*second_operand(char *str);
void	remove_outer_parenth(char **ptr_to_str);
int		is_between_parenth(char *str);
int		check_command_syntax(char *str);
int		is_there_middle_operator(char *str);
int		add_history(const char *);
void	*queue_first(t_queue *q);
void	*queue_pop(t_queue *q);
void	queue_push(t_queue *q, void *data);
void	queue_init(t_queue *q);
void	open_heredoc(char **tokens, int fd);
char	*get_command(char **tokens);
char	**get_args(char **tokens, t_queue *args);
void	**from_queue_to_array(t_queue *q);
t_file	*get_here_doc(t_file *files, int len);
t_file	*get_files(char **tokens, t_operand *op);
t_item	**items_classification(char *line);

#endif
