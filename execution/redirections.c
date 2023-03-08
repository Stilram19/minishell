/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:08:25 by okhiar            #+#    #+#             */
/*   Updated: 2023/03/08 19:10:02 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_infile(t_file *files, int *prev_ifd)
{
	int	infile;

	if (*prev_ifd != -1)
		close(*prev_ifd);
	if (files->type == HERE)
		infile = open(files->pathname, O_RDONLY);
	else
		infile = open(files->pathname, O_RDONLY);
	if (infile == -1)
		open_file_error(files->pathname);
	*prev_ifd = infile;
	return (infile);
}

int	open_outfile(t_file *files, int *prev_ofd)
{
	int	outfile;

	if (*prev_ofd != -1)
		close(*prev_ofd);
	if (is_directory(files->pathname))
	{
		error_msg(ft_strjoin(files->pathname, ": is a directory\n"));
		*prev_ofd = -1;
		return (-1);
	}
	if (files->type == APPEND)
		outfile = open(files->pathname, O_CREAT | O_APPEND | O_WRONLY, 0666);
	else
		outfile = open(files->pathname, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (outfile == -1)
		open_file_error(files->pathname);
	*prev_ofd = outfile;
	return (outfile);
}

t_fdio	*io_rect(t_data *data, t_fdio in, t_fdio out)
{
	int		i;
	int		tmp[2];
	t_fdio	*io_fds;

	i = 0;
	io_fds = init_fdio(in, out);
	tmp[0] = -1;
	tmp[1] = -1;
	while (i < data->f_count)
	{
		if (data->files[i].type == IN || data->files[i].type == HERE)
			io_fds[0].fd = open_infile(&data->files[i], &tmp[0]);
		else if (data->files[i].type == OUT || data->files[i].type == APPEND)
			io_fds[1].fd = open_outfile(&data->files[i], &tmp[1]);
		else
			return (error_msg(" ambiguous redirect\n"), clean_up_of(tmp), NULL);
		if (io_fds[0].fd == -1 || io_fds[1].fd == -1)
			return (clean_up_of(tmp), NULL);
		i++;
	}
	return (io_fds);
}
