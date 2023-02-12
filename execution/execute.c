/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:06:28 by okhiar            #+#    #+#             */
/*   Updated: 2023/02/12 22:12:44 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "build-ins/buildins.h"
#include "helpers.h"

void	clean_up_io(t_redc *r)
{
	dup2(r->dup_in, STDIN_FILENO);
	dup2(r->dup_out, STDOUT_FILENO);
	close(r->dup_in);
	close(r->dup_out);
}

int	execute_buildin(t_cmds *cmds)
{
	int	status;

	status = 0;
	if (!ft_strcmp(cmds->cmd, "cd"))
		status = ft_cd(cmds->args[1]);
	else if (!ft_strcmp(cmds->cmd, "env"))
		status = ft_env();
	else if (!ft_strcmp(cmds->cmd, "pwd"))
		status = ft_pwd();
	else if (!ft_strcmp(cmds->cmd, "echo"))
		status = ft_echo(cmds->args);
	else if (!ft_strcmp(cmds->cmd, "export"))
		status = ft_export(cmds->args);
	else if (!ft_strcmp(cmds->cmd, "exit"))
		exit(0);
	return (status);
}

void	redirect_io(t_cmds *cmds,t_redc *red)
{
	if (cmds->sep == PIPE)
		pipe(red->fds);
	if (cmds->fdin != STDIN_FILENO)
		red->fdin = cmds->fdin;
	else if (cmds->prev && cmds->prev->sep == PIPE)
		red->fdin = red->prev_pipe[0]; // ! Shouldn't closed until next command read from it
	else
		red->fdin = dup(red->dup_in);
	if (cmds->id == cmds->ncmds)
	{
		if (cmds->fdout != STDOUT_FILENO)
			red->fdout = cmds->fdout;
		else
			red->fdout = dup(red->dup_out);
	}
	else if (cmds->sep == PIPE)
		red->fdout = red->fds[1];
	else
		red->fdout = dup(red->dup_out);
}

int	check_sep_op(t_cmds *cmds)
{
	if (cmds->sep == AND_AND || cmds->sep == OR_OR)
		return (1);
	return (0);
}

int	check_exit_status(int status, t_cmds *cmds)
{
	printf("---%d\n", status);
	if (status != 0 && cmds->sep == AND_AND)
		return (1);
	else if (status == 0 && cmds->sep == OR_OR)
		return (1);
	return (0);
}

int	child_exec(t_cmds *cmds)
{
	int	pid;
	int	status;

	pid = fork();
	if (!pid)
	{
		if (is_buildin(cmds->cmd))
		{
			dprintf(2, "%s\n", cmds->cmd);
			status = execute_buildin(cmds);
			exit(status);
		}
		if (ft_execvp(cmds->cmd, cmds->args))
			_ft_putstr_fd(CMN_NF, 2, 127);
	}
	return (pid);
}

int	check_lists(t_cmds *cmds)
{
	if ((cmds->prev && cmds->prev->sep == AND_AND) \
			|| (cmds->prev && cmds->prev->sep == OR_OR))
			return (1);
	if ((cmds->sep == AND_AND) \
			|| (cmds->sep == OR_OR))
		{
			if (cmds->prev && cmds->prev->sep == PIPE)
				return (0);
			return (1);
		}
	return (0);
}

int	exec_cmds(t_cmds *cmds, t_redc *redct)
{
	int	pid;
	int	wt;
	int	b_st;
	int	st_op;

	pid = -1;
	while (cmds)
	{
		wt = check_sep_op(cmds);
		redirect_io(cmds, redct);
		ft_dup2(redct->fdin, 0);
		ft_dup2(redct->fdout, 1);
		if ((check_lists(cmds) || cmds->ncmds == 1) && is_buildin(cmds->cmd))
		{
			b_st = execute_buildin(cmds);
			if (check_exit_status(b_st, cmds))
				break ;
		}
		else
		{
			pid = child_exec(cmds);
			if (wt)
			{
				waitpid(-1, &st_op, 0);
				if (check_exit_status(WEXITSTATUS(st_op), cmds))
					return (pid);
			}
		}
		redct->prev_pipe[0] = redct->fds[0];
		redct->prev_pipe[1] = redct->fds[1];
		cmds = cmds->next;
	}
	return (pid);
}

void	execute(t_cmds *cmds)
{
	t_redc	redct;
	int		status[2];
	int		i;
	int		pid;

	i = -1;
	redct.fdin = 0;
	redct.fdout = 1;
	redct.dup_in = dup(0);
	redct.dup_out = dup(1);
	pid = exec_cmds(cmds, &redct);
	while (++i < cmds->ncmds)
	{
		if (waitpid(-1, &status[0], 0) == pid)
			status[1] = status[0];
	}
	clean_up_io(&redct);
	set_env(get_env(NULL), "?", ft_itoa(WEXITSTATUS(status[1])));
	printf("%d\n", WEXITSTATUS(status[1]));
}

int	main(int ac, char **av, char **env)
{
	t_cmds *cmds;
	t_cmds *cmds2;
	t_cmds *cmds3;

	get_env(env_dup(env));
	ft_env(); 
	printf("----------------------------------------------------------------\n");
	cmds = (t_cmds *)malloc(sizeof(t_cmds));
	cmds2 = (t_cmds *)malloc(sizeof(t_cmds));
	cmds3 = (t_cmds *)malloc(sizeof(t_cmds));
	cmds->ncmds = 1;
	cmds->cmd = ft_strdup("export");
	cmds->args = (char **)malloc(sizeof(char *) * 2);
	cmds->id = 1;
	cmds->args[0] = ft_strdup("blah+=");
	// cmds->args[1] = ft_strdup("LESS=50");
	cmds->args[1] = NULL;
	cmds->fdin = 0;
	cmds->fdout = 1;
	// cmds->hd_fd = hd_fd;
	// cmds->token = HD_TOKEN;
	cmds->sep = 0;
	// cmds->delimiter = ft_strdup("lim");
	cmds->next = NULL;
	cmds->prev = NULL;
	// //**************************************
	// cmds2->ncmds = 3;
	// cmds2->cmd = ft_strdup("exit");
	// cmds2->args = (char **)malloc(sizeof(char *) * 2);
	// cmds2->id = 2;
	// cmds2->args[0] = ft_strdup("exit");
	// cmds2->args[1] = NULL;
	// cmds2->fdin = 0;
	// cmds2->fdout = 1;
	// // cmds2->hd_fd = hd_fd1;
	// // cmds2->token = HD_TOKEN;
	// cmds2->sep = AND_AND;
	// // cmds2->delimiter = ft_strdup("stop");
	// cmds2->next = cmds3;
	// cmds2->prev = cmds;
	// // //***************************************
	// cmds3->ncmds = 3;
	// cmds3->cmd = ft_strdup("exit");
	// cmds3->args = (char **)malloc(sizeof(char *) * 2);
	// cmds3->id = 3;
	// cmds3->args[0] = ft_strdup("exit");
	// // cmds3->args[1] = ft_strdup("5");
	// cmds3->args[1] = NULL;
	// cmds3->fdin = 0;
	// cmds3->fdout = 1;
	// // cmds3->hd_fd = hd_fd1;
	// // cmds3->token = HD_TOKEN;
	// cmds3->sep = 0;
	// // cmds3->delimiter = ft_strdup("stop");
	// cmds3->next = NULL;
	// cmds3->prev = cmds2;
	execute(cmds);
	// sleep(20);
	ft_env();
	return (0);
}
