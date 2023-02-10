/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:30:09 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/10 13:38:19 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	envlen(char **env)
{
	int	i;

	i = 0;
	while (*(env + i))
		i++;
	return (i);
}

/**
 * @brief duplicates the environment variable (the third argument of the main function)
 * in the heap.
*/
char	**env_dup(char **env)
{
	int		i;
	int		var_count;
	char	**my_env;

	i = 0;
	var_count = envlen(env) + 1;
	my_env = ft_garbage_collector(ALLOCATE, var_count * sizeof(char *));
	while (*(env + i))
	{
		*(my_env + i) = ft_strdup(*(env + i));
		i++;
	}
	*(env + i) = NULL;
	return (my_env);
}

/**
 * @brief adds a variable to the environment.
 * @param name {char *} the variable name.
 * @param value {char *} the variable value.
*/
void	set_env(char **my_env, char *name, char *value)
{
	int		i;
	int		var_count;
	char	**new_env;

	i = 0;
	var_count = envlen(my_env) + 2;
	new_env = ft_garbage_collector(ALLOCATE, var_count * sizeof(char *));
	get_env(new_env, UPDATE);
	while (*(my_env + i))
	{
		*(new_env + i) = *(my_env + i);
		i++;
	}
	ft_garbage_collector(SINGLE_RELEASE, 0, my_env);
	*(new_env + i++) = ft_strjoin(name, ft_strjoin("=", value));
	*(new_env + i) = NULL;
}

/**
 * @brief initializes the static variable in the first call,
 * and updates it if the flag is set, and returns its value.
 * @return the value of the static pointer {my_env}
*/
char	**get_env(char **env, int flag)
{
	static char	**my_env;

	if (!my_env)
		my_env = env_dup(env);
	if (flag)
		my_env = env;
	return (my_env);
}
