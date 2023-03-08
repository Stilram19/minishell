/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:23:18 by okhiar            #+#    #+#             */
/*   Updated: 2023/03/08 19:18:46 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child_sig(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		exit(CTRL_C);// ! will checked
	}
}

void	set_exit_status(int status)
{
	char	*var;
	char	**env;

	var = ft_strjoin("?=", ft_itoa(status));
	env = get_env(NULL);
	ft_set_var(env, var, 0);
}

void	ft_dup2(int f1, int f2)
{
	if (f1 == f2)
		return ;
	if (dup2(f1, f2) == -1)
		perror("dup2");
	close(f1);
}

int	check_exit_reason(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status) | 0x80);
	return (status);
}

int	exec_cmds(t_data *cmds, t_fdio in, t_fdio out)
{
	int	pid;
	int	status;
	int	exec_ret;

	cmds->args = wildcards_slice(cmds->args);
	cmds->cmd = cmds->args[0];
	if (is_buildin(cmds->cmd) && defaults_io(in.type, out.type))
		return (exec_buildin(cmds, in, out));
	pid = fork();
	signal(SIGINT, SIG_IGN);
	if (!pid)
	{
		sig_def();
		signal(SIGINT, child_sig);
		ft_dup2(in.fd, 0);
		ft_dup2(out.fd, 1);
		if (is_buildin(cmds->cmd))
			exit(buildins_brute_force(cmds, 0));
		exec_ret = ft_execvp(cmds->cmd, cmds->args);
		if (exec_ret)
			check_fail_reason(exec_ret, cmds->cmd);
	}
	waitpid(pid, &status, 0);
	status = check_exit_reason(status);
	return (status);
}
