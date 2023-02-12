/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:37:40 by okhiar            #+#    #+#             */
/*   Updated: 2023/02/12 10:38:23 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dup2(int f1, int f2)
{
	dprintf(2, "%d %d\n", f1, f2);
	if (f1 != f2)
	{
		if (dup2(f1, f2) == -1)
			perror("dup2");
		close(f1);
	}
}

void	redirect_out(t_cmds *cmds, t_redc *red)
{
	// if (cmds->token == HD_TOKEN)
	// 	return ;
	if (cmds->id == cmds->ncmds)
	{
		if (cmds->fdout != STDOUT_FILENO)
			red->fdout = cmds->fdout;
		else
			red->fdout = dup(red->dup_out);
		return ;
	}
	if (pipe(red->fds))
		_ft_putstr_fd("Error on pipe\n", 2, 1);
	red->fdout = red->fds[1];
	// if (cmds->token == HD_TOKEN)
	// 	red->fdin = dup(red->dup_in);
	// else
		red->fdin = red->fds[0];
}

void	_ft_putstr_fd(char *str, int fd, int ext)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	exit(ext);
}