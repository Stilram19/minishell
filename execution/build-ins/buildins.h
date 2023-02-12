/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 10:31:04 by okhiar            #+#    #+#             */
/*   Updated: 2023/02/12 21:55:56 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDINS_H
# define BUILDINS_H

# include <unistd.h>
# include <stdio.h>
#include "../../minishell.h"

int	ft_cd(char *dir);
int	ft_pwd(void);
int	ft_env(void);
int	ft_echo(char **args);
int	ft_export(char **args);
int	name_len(char *name);
int	valid_arg(char *arg, int *append);

#endif