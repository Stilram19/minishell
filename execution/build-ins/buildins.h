/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 10:31:04 by okhiar            #+#    #+#             */
/*   Updated: 2023/02/18 21:09:14 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDINS_H
# define BUILDINS_H

# include <unistd.h>
# include <stdio.h>
# include "../../minishell.h"

# define RED "\e[1;31m"
# define DEFAULT "\e[0m"

int		ft_cd(char **args);
int		ft_pwd(void);
int		ft_env(void);
int		ft_exit(char **args);
int		ft_echo(char **args);
int		ft_unset(char **args);
int		ft_export(char **args);
int		name_len(char *name, int *append);
int		valid_arg(char *arg, int *append);
int		is_exist(char **env, char *identifier);
void	ft_set_var(char **env, char *var, int append);

#endif