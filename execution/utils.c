/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:23:18 by okhiar            #+#    #+#             */
/*   Updated: 2023/02/15 17:56:50 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmds	*command_fill(char *cmd, int fd_in, int fd_out)
{
	t_cmds	*cmd_s;

	cmd_s = (t_cmds *)malloc(sizeof(t_cmds));
	cmd_s->cmd = ft_strdup(cmd);
	cmd_s->args = (char **)malloc(sizeof(char *) * 2);
	cmd_s->args[0] = ft_strdup(cmd);
	cmd_s->args[1] = NULL;
	cmd_s->fd_in = fd_in;
	cmd_s->fd_out = fd_out;
	return (cmd_s);
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