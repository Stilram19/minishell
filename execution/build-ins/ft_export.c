/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:54:29 by okhiar            #+#    #+#             */
/*   Updated: 2023/02/13 18:06:25 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

void	check_append(char **env_v, char *v, char *val, int app)
{
	if (!val[0] && !app)
		return ;
	if (app)
	{
		if (!ft_strchr(*env_v, '='))
			*env_v = ft_strjoin(*env_v, "=");
		*env_v = ft_strjoin(*env_v, val);
	}
	else
		*env_v = ft_strdup(v);
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
		new_env[i] = ft_strjoin(var_name, ft_strjoin("=", var_value));
	else
		new_env[i] = ft_strdup(var);
	new_env[i + 1] = NULL;
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

int	ft_export(char **args)// !  export "x=gh"=10
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
