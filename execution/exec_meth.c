/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_meth.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 12:37:46 by okhiar            #+#    #+#             */
/*   Updated: 2023/02/12 14:53:01 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"


void	create_pipe(int *fds)
{
	if (pipe(fds))
		_ft_putstr_fd("Error\n", 2, 1);
	dup2(fds[1], STDOUT_FILENO);
	close(fds[1]);
}

void	clean_up_io(t_redc *r)
{
	dup2(r->dup_in, STDIN_FILENO);
	dup2(r->dup_out, STDOUT_FILENO);
	close(r->dup_in);
	close(r->dup_out);
}

void	redirect_out(t_cmds *cmds, t_redc *redc)
{
	if (cmds->id == cmds->ncmds)
	{
		if (cmds->fdout == 1)
			cmds->fdout = dup(redc->dup_out);
		dup2(cmds->fdout, STDOUT_FILENO);
		close(cmds->fdout);
	}
	else
		create_pipe(redc->fds);
}

int	simple_exec(t_cmds *cmds)
{
	int	status;
	int	pid;

	if (is_buildin(cmds->cmd))
		return (execute_buildin(cmds));
	else
	{
		pid = fork();
		if (pid == 0)
			if (ft_execvp(cmds->cmd, cmds->args))
				_ft_putstr_fd(CMN_NF, 2, 127);
		waitpid(pid, &status, 0);
	}
	return (WEXITSTATUS(status));
}

int	complex_exec(t_cmds *cmds)
{
	t_redc	redct;
	int		pid;
	int		status;

	redct.dup_in = dup(0);
	redct.dup_out = dup(1);
	create_pipe(redct.fds);
	if (cmds->fdin != STDIN_FILENO)
		dup2(cmds->fdin, STDIN_FILENO);
	while (cmds)
	{
		if (is_buildin(cmds->cmd))
			execute_buildin(cmds);
		else
		{
			pid = fork();
			if (!pid)
				if (ft_execvp(cmds->cmd, cmds->args))
					_ft_putstr_fd(CMN_NF, 2, 127);
		}
		cmds = cmds->next;
		if (!cmds)
			break ;
		dup2(redct.fds[0], 0);
		close(redct.fds[0]);
		redirect_out(cmds, &redct);
	}
	int	i = -1;
	while (++i < 2) // ! Warning
		waitpid(-1, &status, 0);
	clean_up_io(&redct);
	return (WEXITSTATUS(status));
}

int	execute(t_cmds *cmds)
{
	int	status;
	if (cmds->ncmds == 1)
		status = simple_exec(cmds);
	else
		status = complex_exec(cmds);
	set_env(get_env(NULL), "?", ft_itoa(status));
	return (0);
}


/*
int	exec_cmds(t_cmds *cmds, t_redc *redct)
{
	int	pid;

	pid = -1;
	if (cmds->fdin != STDIN_FILENO)
		redct->fdin = cmds->fdin;
	while (cmds)
	{
		ft_dup2(redct->fdin, 0);
		redirect_out(cmds, redct);
		ft_dup2(redct->fdout, 1);
		if (is_buildin(cmds->cmd))
			execute_buildin(cmds);
		else
		{
			pid = fork();
			if (!pid)
				if (ft_execvp(cmds->cmd, cmds->args))
					_ft_putstr_fd(CMN_NF, 2, 127);
		}
		cmds = cmds->next;
	}
	return (pid);
}*/