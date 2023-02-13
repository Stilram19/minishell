/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:19:07 by okhiar            #+#    #+#             */
/*   Updated: 2023/02/13 18:06:13 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

void	unset_var_env(char **env, char *name)
{
	int		i;
	int		j;
	int		len;
	int		index;
	char	**new_env;

	i = 0;
	j = 0;
	index = is_exist(env, name);
	if (index == -1)
		return ;
	len = envlen(env);
	new_env = (char **)malloc(sizeof(char *) * len);
	if (!new_env)
		return ;
	while (env[i])
	{
		if (i != index)
			new_env[j++] = env[i];
		i++;
	}
	new_env[j] = NULL;
	get_env(new_env);
}

int	ft_unset(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (valid_arg(args[i], NULL))
			unset_var_env(get_env(NULL), args[i]);
		else
		{
			ft_putstr_fd("\e[1;31munset:\e[0m invalid identifier\n", 2);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
