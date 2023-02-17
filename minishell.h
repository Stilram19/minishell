/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:49:24 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/17 15:10:51 by obednaou         ###   ########.fr       */
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

int		is_blank(char c);
char	**get_env(char **env);
char	**env_dup(char **env);
char	*get_var_value(char *key);
void	expanding(char **tokens);
void	remove_quotes(char **tokens);
void	set_env(char **my_env, char *name, char *value);
void	*ft_garbage_collector(int option, int size, void *to_free);
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
void	remove_outer_brackets(char **ptr_to_str);
int		is_between_brackets(char *str);
int		check_command_syntax(char *str);
int		is_there_middle_operator(char *str);

#endif
