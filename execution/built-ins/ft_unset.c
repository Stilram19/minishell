/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:19:07 by okhiar            #+#    #+#             */
/*   Updated: 2023/03/08 11:41:38 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	free(env[index]);
	free(env);
	new_env[j] = NULL;
	get_env(new_env);
}

int	ft_unset(char **args)
{
	int	i;
	int	status;

	i = 0;
	status = EXIT_SUCCESS;
	while (args[i])
	{
		if (valid_arg(args[i], NULL))
			unset_var_env(get_env(NULL), args[i]);
		else
			status = (ft_putstr_fd("\e[1;31munset:\e[0m invalid identifier\n", 2), \
			1);
		i++;
	}
	return (status);
}
