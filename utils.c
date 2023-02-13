/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:30:09 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/13 13:54:15 by okhiar           ###   ########.fr       */
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
	my_env = ft_garbage_collector(ALLOCATE, var_count * sizeof(char *), NULL);
	while (*(env + i))
	{
		*(my_env + i) = ft_strdup(*(env + i));
		i++;
	}
	*(my_env + i) = NULL;
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
	new_env = ft_garbage_collector(ALLOCATE, var_count * sizeof(char *), NULL);
	get_env(new_env);
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
char	**get_env(char **env)
{
	static char	**my_env;

	if (env)
		my_env = env;
	return (my_env);
}

/**
 * @brief Get the value of a variable on the environment variables
 * by its key (name)
 * 
 * @param key name of the variable
 * @return char* the value of the variable
 */
char	*get_env_var(char *key)
{
	int		i;
	char	**env;

	i = 0;
	env = get_env(NULL);
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, ft_strlen(key)) \
					&& env[i][ft_strlen(key)] == '=')
			return (ft_strdup(env[i] + (ft_strlen(key) + 1)));
		i++;
	}
	return (NULL);
}