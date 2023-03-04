/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 10:30:31 by okhiar            #+#    #+#             */
/*   Updated: 2023/03/04 15:20:46 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_putstr_fd__(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		write(fd, &str[i++], 1);
}

char	*check_dir(char *arg)
{
	char	*dir;
	// char	*key;

	if (!arg)
	{
		dir = get_var_value("HOME");
		if (!dir)
			ft_putstr_fd__("cd: HOME not set\n", 2);
	}
	else if (!ft_strcmp(arg, "-"))
	{
		dir = get_var_value("OLDPWD");
		if (!dir)
			ft_putstr_fd__("cd: OLDPWD not set\n", 2);
	}
	else
		dir = arg;
	return (dir);
}

int	ft_cd(char **args)
{
	char	*dir;
	char	*owd;
	char	*cwd;

	owd = getcwd(NULL, 0);
	dir = check_dir(args[0]);
	if (!dir || !owd)
		return (EXIT_FAILURE);
	if (chdir(dir))
	{
		perror("CD");
		// ft_putstr_fd__("cd: no such file or directory\n", 2);
		return (EXIT_FAILURE);
	}
	if (ft_strcmp(dir, ".") && ft_strcmp(dir, "..") && args[0])
		ft_pwd();
	cwd = getcwd(NULL, 0);
	ft_set_var(get_env(NULL), ft_strjoin("OLDPWD=", owd), 0);
	ft_set_var(get_env(NULL), ft_strjoin("PWD=", cwd), 0);
	return (EXIT_SUCCESS);
}
