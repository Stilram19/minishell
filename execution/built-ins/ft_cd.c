/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 10:30:31 by okhiar            #+#    #+#             */
/*   Updated: 2023/03/08 21:31:01 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*check_dir(char *arg)
{
	char	*dir;

	if (!arg)
	{
		dir = get_var_value("HOME");
		if (!dir)
			ft_putstr_fd("cd: HOME not set\n", 2);
	}
	else if (!ft_strcmp(arg, "-"))
	{
		dir = get_var_value("OLDPWD");
		if (!dir)
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
	}
	else
		dir = arg;
	return (dir);
}

void	set_working_dir(char *str, char *owd)
{
	char	*old_curr_wd;

	old_curr_wd = owd;
	if (!owd)
		old_curr_wd = getcwd(NULL, 0);
	if (!old_curr_wd)
		return ;
	ft_set_var(get_env(NULL), ft_strjoin(str, old_curr_wd), 0);
	free(old_curr_wd);
}

int	ft_cd(char **args)
{
	char	*dir;
	char	*old_working_dir;

	old_working_dir = getcwd(NULL, 0);
	dir = check_dir(args[0]);
	if (!dir)
	{
		if (old_working_dir)
			free(old_working_dir);
		return (EXIT_FAILURE);
	}
	if (chdir(dir))
	{
		ft_putstr_fd(ft_strjoin(ft_strjoin("cd: ", dir), \
		": no such file or directory\n"), 2);
		return (EXIT_FAILURE);
	}
	if (old_working_dir)
		set_working_dir("OLDPWD=", old_working_dir);
	if (ft_strcmp(dir, ".") && ft_strcmp(dir, "..") && args[0])
		ft_pwd();
	set_working_dir("PWD=", NULL);
	return (EXIT_SUCCESS);
}
