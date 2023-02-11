/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:37:40 by okhiar            #+#    #+#             */
/*   Updated: 2023/02/11 18:23:32 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dup2(int f1, int f2)
{
	//dprintf(2, "%d %d\n", f1, f2);
	if (f1 != f2)
	{
		if (dup2(f1, f2) == -1)
			perror("dup2");
		close(f1);
	}
}

void	redirect_out(t_cmds *cmds, t_redc *red)
{
	if (cmds->token == HD_TOKEN)
		return ;
	if (cmds->id == cmds->ncmds)
	{
		// dprintf(2, "here\n");
		if (cmds->fdout != STDOUT_FILENO)
			red->fdout = cmds->fdout;
		else
		{
			red->fdout = dup(red->dup_out);
			// sleep(50);
		}
		return ;
	}
	if (pipe(red->fds))
		_ft_putstr_fd("Error on pipe\n", 2, 1);
	red->fdout = red->fds[1];
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