/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:31:54 by okhiar            #+#    #+#             */
/*   Updated: 2023/03/07 16:48:43 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_fdio	*set_io_type(int *fds, int type)
{
	t_fdio	*fd_io;

	fd_io = ft_garbage_collector(ALLOCATE, sizeof(t_fdio) * 2, NULL);
	fd_io[0].fd = fds[0];
	fd_io[0].type = type;
	fd_io[1].fd = fds[1];
	fd_io[1].type = type;
	return (fd_io);
}

int	is_directory(char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
		return (1);
	return (0);
}

int	io_subs_type(t_fdio *in, t_fdio *out)
{
	in->type = SUB_EXEC;
	out->type = SUB_EXEC;
	return (1);
}

int	defaults_io(int in_type, int out_type)
{
	if (in_type != C_EXEC && out_type != C_EXEC)
		return (1);
	return (0);
}
