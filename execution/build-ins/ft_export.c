/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:54:29 by okhiar            #+#    #+#             */
/*   Updated: 2023/02/12 22:16:40 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"


int	is_exist(char **env, char *identifier)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(identifier);
	while (env[i])
	{
		if (!ft_strncmp(identifier, env[i], len) \
			&& (!env[i][len] || env[i][len] == '='))
			return (i);
		i++;
	}
	return (-1);
}

void	ft_set_var(char **env, char *var, int append)
{
	int		i;
	int		index;
	char	**new_env;
	char	*var_name;
	char	*var_value;

	i = -1;
	var_name = ft_substr(var, 0, name_len(var) - append);
	var_value = ft_substr(var, name_len(var) + 1, ft_strlen(var));
	index = is_exist(env, var_name);
	if (index != -1)
	{
		if (append)
			env[index] = ft_strjoin(env[index], var_value);
		else
			env[index] = ft_strdup(var);
		return ;
	}
	new_env = (char **)malloc(sizeof(char *) * (envlen(env) + 2));
	while (env[++i])
		new_env[i] = env[i];
	if (append)
		new_env[i] = ft_strjoin(var_name, ft_strjoin("=", var_value));
	else
		new_env[i] = ft_strdup(var);
	get_env(new_env);
}

void	ft_print_set(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd(env[i], 1);
		write(1, "\n", 1);
		i++;
	}
}

int	ft_export(char **args)
{
	int	i;
	int	status;
	int	append;

	i = 0;
	status = 0;
	if (!args[0])
		ft_print_set(get_env(NULL));
	while (args[i])
	{
		if (valid_arg(args[i], &append))
			ft_set_var(get_env(NULL), args[i], append);
		else
		{
			ft_putstr_fd("invalid identifier\n", 2);
			status = 1;
		}
		i++;
	}
	return (status);
}