/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 14:00:52 by okhiar            #+#    #+#             */
/*   Updated: 2023/03/08 23:26:50 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_pathjoin(char *file, char *path)
{
	char	*tmp;
	char	*ret;

	tmp = ft_strjoin1(path, "/");
	ret = ft_strjoin1(tmp, file);
	free(tmp);
	return (ret);
}

// int	check_if_on_cwd(char *path)
// {
// 	struct dirent	*dir_entry;
// 	DIR				*dir_ptr;

// 	dir_ptr = opendir(".");
// 	if (!dir_ptr)
// 		return (0);
// 	dir_entry = readdir(dir_ptr);
// 	while (dir_entry)
// 	{
// 		if (!ft_strcmp(dir_entry->d_name, path))
// 		{
// 			closedir(dir_ptr);
// 			return (1);
// 		}
// 		dir_entry = readdir(dir_ptr);
// 	}
// 	closedir(dir_ptr);
// 	return (0);
// }

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
	free(strs);
	strs = NULL;
	return (NULL);
}

int	check_exist_bin(char *file, char *path)
{
	int		i;
	char	**paths;
	char	*file_path;

	if (!path)
		return (1);
	paths = _ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		file_path = ft_pathjoin(file, paths[i]);
		if (!access(file_path, X_OK))
		{
			free_all(paths);
			free(file_path);
			return (0);
		}
		free(file_path);
		i++;
	}
	free_all(paths);
	return (1);
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
static char	*valid_cmd(char *file, char *path)
{
	size_t	i;
	char	**paths;
	char	*file_path;

	i = 0;
	if (!access(file, X_OK) && (check_exist_bin(file, path) || file[0] == '.'))
		return (ft_strdup1(file));
	if (!path)
		return (0);
	paths = _ft_split(path, ':');
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
 * @brief will duplicate the actions of the shell in searching,
 *  for an executable file,
 *  if the specified file name does not contain a slash "/" character. 
 * ft_execvp(@file, @args), search path is the path specified in 
 * the environment by "PATH" variable.
 * 
 * @param file 
 * @param args 
 * @return int 
 */
int	ft_execvp(char *file, char **args)
{
	char	*cmd;
	char	*path;

	path = get_var_value("PATH");
	cmd = valid_cmd(file, path);
	if (!access(file, F_OK) \
		&& access(file, X_OK) && file[0] == '.')
		return (-2);
	if (!cmd)
		return (-1);
	if (execve(cmd, args, get_env(NULL)))
		return (-1);
	return (0);
}
