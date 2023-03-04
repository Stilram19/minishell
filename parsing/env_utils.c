/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 12:54:03 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/04 16:30:01 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


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
	int		size;
	char	**my_env;

	i = 0;
	size = envlen(env) + 1;
	my_env = malloc(sizeof(void *) * size);
	while (*(env + i))
	{
		*(my_env + i) = ft_strdup1(*(env + i));
		i++;
	}
	*(my_env + i) = NULL;
	return (my_env);
}

/**
 * @brief Get the value of a variable on the environment variables
 * by its key (name)
 * 
 * @param key name of the variable
 * @return char* the value of the variable
 */
char	*get_var_value(char *key)
{
	int		i;
	int		key_len;
	char	**env;

	i = 0;
	key_len = ft_strlen(key);
	env = get_env(NULL);
	while (env[i])
	{
        if (!ft_strncmp(env[i], key, key_len)
			&& env[i][key_len] == '=')
        return (ft_strdup(env[i] + (key_len + 1)));
        i++;
    }
    return (NULL);
}

/**
 * @brief adds a variable to the environment.
 * @param name {char *} the variable name.
 * @param value {char *} the variable value.
*/
void	set_env(char **old_env, char *name, char *value)
{
	int		i;
	int		new_size;
	char	**new_env;
	char	*temp;

	i = 0;
	new_size = envlen(old_env) + 2;
	new_env = malloc(sizeof(void *) * new_size);
	get_env(new_env);
	while (*(old_env + i))
	{
		*(new_env + i) = *(old_env + i);
		i++;
	}
	temp = ft_strjoin1("=", value);
	*(new_env + i++) = ft_strjoin1(name, temp);
	free(temp);
	free(old_env);
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
