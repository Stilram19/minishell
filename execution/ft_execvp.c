 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 18:35:03 by okhiar            #+#    #+#             */
/*   Updated: 2023/01/31 21:44:15 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(void);

char	*ft_pathjoin(char *file, char *path)
{
	char	*tmp;
	char	*ret;

	tmp = ft_strjoin(path, "/");
	ret = ft_strjoin(tmp, file);
	free(tmp);
	return (ret);
}

static char	**free_all(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		strs[i] = 0;
		i++;
	}
	free(strs[i]);
	strs[i] = 0;
	free(strs);
	strs = NULL;
	return (NULL);
}

/**
 * @brief Function That Checks if The file is executable
 * in case full path it will return dupplicate of the path
 * otherwise it will concatenate the path with the the set of
 * $PATH variable on the ENV
 * 
 * @param file file name
 * @param path the set of path variables
 * @return char* the address of the valid path, or NULL if it is not
 */
char	*valid_cmd(char *file, char *path)
{
	size_t	i;
	char	**paths;
	char	*file_path;

	i = 0;
	if (!access(file, X_OK))
		return (ft_strdup(file));
	if (!path)
		return (0);
	paths = ft_split(path, ':');
	if (!paths)
		return (0);
	while (paths[i])
	{
		file_path = ft_pathjoin(file, paths[i]);
		if (!access(file_path, X_OK))
		{
			free_all(paths);
			return (file_path);
		}
		free(file_path);
		i++;
	}
	free_all(paths);
	return (0);
}

/**
 * @brief execute the specified command
 * 
 * @param file 
 * @param args 
 * @param env 
 * @return int 
 */
int	ft_execvp(char *file, char **args)
{
	char	*cmd;
	char	*path;

	path = get_env_var("PATH");
	cmd = valid_cmd(file, path);
	if (!cmd)
		return (-1);
	// dprintf(2, "%s\n", args[1]);
	if (execve(cmd, args, get_env(NULL)))
		return (-1);
	return (0);
}
