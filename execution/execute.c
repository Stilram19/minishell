/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:06:28 by okhiar            #+#    #+#             */
/*   Updated: 2023/02/10 16:38:32 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_buildin(t_cmds *cmds)
{
	if (!ft_strcmp(cmds->cmd, "cd"))
		ft_cd(cmds->args[1]);
}

int	execute(t_cmds *cmds)
{
	t_redc	redct;

	redct.fdin = 0;
	redct.tmpin = dup(0);
	redct.tmpout = dup(1);
	if (cmds->fdin != STDIN_FILENO)
		redct.fdin = cmds->fdin;
	while (cmds)
	{
		dup2(redct.fdin, 0);
		if (cmds->id == cmds->ncmds - 1)
			dup2(cmds->fdout, 1);
		if (is_buildin(cmds->cmd))
			execute_buildin(cmds);
		else
	}
	return (0);
}
