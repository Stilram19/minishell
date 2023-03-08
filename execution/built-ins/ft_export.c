/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:54:29 by okhiar            #+#    #+#             */
/*   Updated: 2023/03/08 23:39:57 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_append(char **env_v, char *v, char *val, int app)
{
	char	*tmp;

	if (!val[0] && !app && !ft_strchr(v, '='))
		return ;
	tmp = *env_v;
	if (app)
	{
		if (!ft_strchr(*env_v, '='))
			*env_v = ft_strjoin(*env_v, "=");
		*env_v = ft_strjoin1(*env_v, val);
	}
	else
		*env_v = ft_strdup1(v);
	free(tmp);
}

void	ft_set_var(char **env, char *var, int append)
{
	int		i;
	int		index;
	char	**new_env;
	char	*var_name;
	char	*var_value;

	i = -1;
	var_name = ft_substr(var, 0, name_len(var, &append) - append);
	var_value = ft_substr(var, name_len(var, &append) + 1, ft_strlen(var));
	index = is_exist(env, var_name);
	if (index != -1)
	{
		check_append(&env[index], var, var_value, append);
		return ;
	}
	new_env = (char **)malloc(sizeof(char *) * (envlen(env) + 2));
	while (env[++i])
		new_env[i] = env[i];
	if (append)
		new_env[i] = ft_strjoin1(var_name, ft_strjoin("=", var_value));
	else
		new_env[i] = ft_strdup1(var);
	new_env[i + 1] = NULL;
	free(env);
	get_env(new_env);
}

int	id_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

void	ft_print_set(char **env)
{
	char	*identifier;
	char	*value;
	int		i;
	int		len;

	i = 0;
	while (env[i])
	{
		len = id_len(env[i]);
		identifier = ft_substr(env[i], 0, id_len(env[i]));
		if (env[i][len] == '=')
		{
			value = ft_substr(env[i], id_len(env[i]) + 1, ft_strlen(env[i]));
			printf("%s=\"%s\"\n", identifier, value);
		}
		else
			ft_putendl_fd(env[i], 1);
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
			(status = (ft_putstr_fd("\e[1;31mexport:\e[0m invalid identifier\n", \
								2), 1));
		i++;
	}
	return (status);
}
