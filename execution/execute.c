/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:06:28 by okhiar            #+#    #+#             */
/*   Updated: 2023/02/10 21:55:44 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "build-ins/buildins.h"

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

int	execute_buildin(t_cmds *cmds)
{
	int	status;

	if (!ft_strcmp(cmds->cmd, "cd"))
		status = ft_cd(cmds->args[1]);
	else if (!ft_strcmp(cmds->cmd, "env"))
		status = ft_env();
	else if (!ft_strcmp(cmds->cmd, "pwd"))
		status = ft_pwd();
	return (0);
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

// int	main(int ac, char **av, char **env)
// {
// 	t_cmds *cmds;
// 	t_cmds *cmds2;

// 	get_env(env_dup(env));
// 	// ft_env();
// 	int fdout = open("file", O_RDONLY, 0666);
// 	printf("----------------------------------------------------------------\n");
// 	cmds = (t_cmds *)malloc(sizeof(t_cmds));
// 	cmds2 = (t_cmds *)malloc(sizeof(t_cmds));
// 	cmds->ncmds = 2;
// 	cmds->cmd = ft_strdup("pwd");
// 	cmds->args = (char **)malloc(sizeof(char *) * 2);
// 	cmds->id = 1;
// 	cmds->args[0] = ft_strdup("pwdl");
// 	cmds->args[1] = NULL;
// 	cmds->fdin = fdout;
// 	cmds->fdout = 1;
// 	cmds->next = cmds2;
// 	//*************************
// 	cmds2->ncmds = 2;
// 	cmds2->cmd = ft_strdup("wc");
// 	cmds2->args = (char **)malloc(sizeof(char *) * 2);
// 	cmds2->id = 2;
// 	cmds2->args[0] = ft_strdup("wc");
// 	cmds2->args[1] = NULL;
// 	cmds2->fdin = 0;
// 	cmds2->fdout = 1;
// 	cmds2->next = NULL;
// 	int status = execute(cmds);
// 	// ft_env();
// 	return (status);
// }

// int	execute(t_cmds *cmds)
// {
// 	t_redc	redct;
// 	int		pid;
// 	int		status;

// 	redct.fdin = 0;
// 	redct.tmpin = dup(0);
// 	redct.tmpout = dup(1);
// 	if (cmds->fdin != STDIN_FILENO)
// 		redct.fdin = cmds->fdin;
// 	while (cmds)
// 	{
// 		dup2(redct.fdin, 0);
// 		if (cmds->id == cmds->ncmds - 1)
// 		{
// 			if (cmds->fdout != STDOUT_FILENO)
// 				redct.fdout = cmds->fdout;
// 			else
// 				redct.fdout = dup(redct.tmpout);
// 		}
// 		else
// 		{
// 			pipe(redct.fds);
// 			redct.fdout = redct.fds[1];
// 			redct.fdin = redct.fds[0];
// 		}
// 		dup2(redct.fdout, 1);
// 		close(redct.fdout);
// 		if (is_buildin(cmds->cmd))
// 			execute_buildin(cmds);
// 		else
// 		{
// 			pid = fork();
// 			if (!pid)
// 				if (ft_execvp(cmds->cmd, cmds->args, get_env(NULL)))
// 					_ft_putstr_fd("\e[1;31Minishell\e[0m : Command not found", 2, 1);
// 		}
// 	}
// 	waitpid(pid, &status, 0);
// 	return (WEXITSTATUS(status));
// }
