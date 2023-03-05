/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:23:18 by okhiar            #+#    #+#             */
/*   Updated: 2023/03/05 14:21:46 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	defaults_io(int in_type, int out_type)
{
	if (in_type != PIPE_IO && out_type != PIPE_IO)
		return (1);
	return (0);
}

t_fdio	*set_io_type(int *fds, int type)
{
	t_fdio	*fd_io;

	fd_io = (t_fdio *)malloc(sizeof(t_fdio) * 2);
	fd_io[0].fd = fds[0];
	fd_io[0].type = type;
	fd_io[1].fd = fds[1];
	fd_io[1].type = type;
	return (fd_io);
}

int	check_exit_reason(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status) | 0x80);
	return (status);
}
