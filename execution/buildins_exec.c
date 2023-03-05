/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:14:31 by okhiar            #+#    #+#             */
/*   Updated: 2023/03/05 15:36:08 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	io_cleanup(int in, int out)
{
	ft_dup2(in, 0);
	ft_dup2(out, 1);
}

int	buildins_brute_force(t_data *cmds, int flag)
{
	int	status;

	status = 0;
	if (!ft_strcmp(cmds->cmd, "cd"))
		status = ft_cd(cmds->args + 1);
	else if (!ft_strcmp(cmds->cmd, "env"))
		status = ft_env();
	else if (!ft_strcmp(cmds->cmd, "pwd"))
		status = ft_pwd();
	else if (!ft_strcmp(cmds->cmd, "echo"))
		status = ft_echo(cmds->args + 1);
	else if (!ft_strcmp(cmds->cmd, "export"))
		status = ft_export(cmds->args + 1);
	else if (!ft_strcmp(cmds->cmd, "unset"))
		status = ft_unset(cmds->args + 1);
	else if (!ft_strcmp(cmds->cmd, "exit"))
		status = ft_exit(cmds->args + 1, flag);
	return (status);
}

int	exec_buildin(t_data *cmds, int in, int out)
{
	int	status;
	int	tmp_io[2];

	tmp_io[0] = dup(0);
	tmp_io[1] = dup(1);
	ft_dup2(in, 0);
	ft_dup2(out, 1);
	status = buildins_brute_force(cmds, 1);
	io_cleanup(tmp_io[0], tmp_io[1]);
	return (status);
}
