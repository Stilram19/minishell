/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:06:00 by okhiar            #+#    #+#             */
/*   Updated: 2023/03/08 19:09:12 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_fdio	*init_fdio(t_fdio in, t_fdio out)
{
	t_fdio	*io_fds;

	io_fds = ft_garbage_collector(ALLOCATE, sizeof(t_fdio) * 2, NULL);
	io_fds[0].fd = in.fd;
	io_fds[1].fd = out.fd;
	io_fds[0].type = in.type;
	io_fds[1].type = out.type;
	return (io_fds);
}

void	clean_up_of(int *io)
{
	if (io[0] != -1)
		close(io[0]);
	if (io[1] != -1)
		close(io[1]);
}

void	open_file_error(char *file)
{
	if (!access(file, F_OK))
		error_msg(ft_strjoin(file, ": Permission denied\n"));
	else
		error_msg(ft_strjoin(file, ": No such file or directory\n"));
}
