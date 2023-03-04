/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:08:25 by okhiar            #+#    #+#             */
/*   Updated: 2023/03/04 22:31:14 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirect_error(int error_key, int ext)
{
	if (error_key == AMBIG_ERR)
		ft_putstr_fd("\e[1;31mMinishell:\e[0m ambiguous redirect\n", 2);
	else
		ft_putstr_fd("\e[1;31mMinishell:\e[0m No such file or directory\n", 2);
	if (ext)
		exit(EXIT_FAILURE);
	return (EXIT_FAILURE);
}

t_fdio	*init_fdio(t_fdio in, t_fdio out)
{
	t_fdio	*io_fds;

	io_fds = (t_fdio *)malloc(sizeof(t_fdio) * 2);
	io_fds[0].fd = in.fd;
	io_fds[1].fd = out.fd;
	io_fds[0].type = in.type;
	io_fds[1].type = out.type;
	return (io_fds);
}

int	is_directory(char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
		return (1);
	return (0);
}

int	open_infile(t_file *files, int type, int prev_ifd)
{
	int	infile;

	if (prev_ifd != -1)
		close(prev_ifd);
	if (type == HERE)
		return (files->here_fd);
	infile = open(files->pathname, O_RDONLY);
	return (infile);	
}

int	open_outfile(t_file *files, int type, int prev_ofd)
{
	int	outfile;

	if (prev_ofd != -1)
		close(prev_ofd);
	if (type == APPEND)
		return (open(files->pathname, O_CREAT | O_APPEND| O_WRONLY, 0666));
	outfile = open(files->pathname, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	return (outfile);
}

t_fdio	*io_rect(t_data *data, t_fdio in, t_fdio out)
{
	int	i;
	int	tmp[2];
	t_fdio	*io_fds;

	i = 0;
	io_fds = init_fdio(in, out);
	tmp[0] = -1;
	tmp[1] = -1;
	while (i < data->f_count)
	{
		if (data->files[i].type == IN || data->files[i].type == HERE)
		{
			io_fds[0].fd = open_infile(&data->files[i], data->files[i].type, tmp[0]);
			tmp[0] = io_fds[0].fd;
		}
		else if (data->files[i].type == OUT || data->files[i].type == APPEND)// ! check if is a directory
		{
			io_fds[1].fd = open_outfile(&data->files[i], data->files[i].type, tmp[1]);
			tmp[1] = io_fds[1].fd;
		}
		else
			return (NULL); // ! before return you must call close
		if (io_fds[0].fd == -1 || io_fds[1].fd == -1)
			return (NULL); // ! before return you must call close
		i++;
	}
	return (io_fds);
}
