/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:06:28 by okhiar            #+#    #+#             */
/*   Updated: 2023/02/11 15:12:07 by okhiar           ###   ########.fr       */
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
	return (status);
}

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
}

void	execute(t_cmds *cmds)
{
	t_redc	redct;
	int		status;
	int		i;
	int		pid;

	i = -1;
	redct.fdin = 0;
	redct.dup_in = dup(0);
	redct.dup_out = dup(1);
	pid = exec_cmds(cmds, &redct);
	while (++i < cmds->ncmds)
		waitpid(-1, &status, 0);
	clean_up_io(&redct);
	set_env(get_env(NULL), "?", ft_itoa(WEXITSTATUS(status)));
}

// int	main(int ac, char **av, char **env)
// {
// 	t_cmds *cmds;
// 	t_cmds *cmds2;

// 	get_env(env_dup(env));
// 	ft_env();
// 	int fdin = open("file", O_RDONLY, 0666);
// 	printf("----------------------------------------------------------------\n");
// 	cmds = (t_cmds *)malloc(sizeof(t_cmds));
// 	cmds2 = (t_cmds *)malloc(sizeof(t_cmds));
// 	cmds->ncmds = 2;
// 	cmds->cmd = ft_strdup("sleep");
// 	cmds->args = (char **)malloc(sizeof(char *) * 3);
// 	cmds->id = 1;
// 	cmds->args[0] = ft_strdup("sleep");
// 	cmds->args[1] = ft_strdup("5");
// 	cmds->args[2] = NULL;
// 	cmds->fdin = 0;
// 	cmds->fdout = 1;
// 	cmds->next = cmds2;
// 	// //*************************
// 	cmds2->ncmds = 2;
// 	cmds2->cmd = ft_strdup("dksj");
// 	cmds2->args = (char **)malloc(sizeof(char *) * 2);
// 	cmds2->id = 2;
// 	cmds2->args[0] = ft_strdup("dskj");
// 	cmds2->args[1] = NULL;
// 	cmds2->fdin = 0;
// 	cmds2->fdout = 1;
// 	cmds2->next = NULL;
// 	execute(cmds);
// 	ft_env();
// 	return (0);
// }
