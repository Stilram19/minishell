/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:08:25 by okhiar            #+#    #+#             */
/*   Updated: 2023/03/04 14:55:30 by okhiar           ###   ########.fr       */
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

int	is_directory(char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
		return (1);
	return (0);
}

int	open_infile(t_file *files, int type)
{
	int	infile;

	if (type == HERE)
		return (files->here_fd);
	infile = open(files->pathname, O_RDONLY);
	return (infile);	
}

int	open_outfile(t_file *files, int type)
{
	int	outfile;

	if (type == APPEND)
		return (open(files->pathname, O_CREAT | O_APPEND| O_WRONLY, 0666));
	outfile = open(files->pathname, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	return (outfile);
}

int	*io_rect(t_data *data, int in, int out)
{
	int	i;
	int	tmp[2];
	int	*io_fds;

	i = 0;
	io_fds = (int *)malloc(sizeof(int) * 2);
	io_fds[0] = in;
	io_fds[1] = out;
	tmp[0] = -1;
	tmp[1] = -1;
	while (i < data->f_count)
	{
		// printf("here %d\n", i);
		if (data->files[i].type == IN || data->files[i].type == HERE)
		{
			if (tmp[0] != -1)
				close(io_fds[0]);
			io_fds[0] = open_infile(&data->files[i], data->files[i].type);
			tmp[0] = io_fds[0];
		}
		else if (data->files[i].type == OUT || data->files[i].type == APPEND)// ! check if is a directory
		{
			if (tmp[1] != -1)
				close(io_fds[1]);
			io_fds[1] = open_outfile(&data->files[i], data->files[i].type);
			tmp[1] = io_fds[1];
		}
		else
			return (NULL); // ! before return you must call close
		if (io_fds[0] == -1 || io_fds[1] == -1)
			return (NULL); // ! before return you must call close
		i++;
	}
	return (io_fds);
}


// int	redirect_io(t_operand *cmds, int in, int out)
// {
// 	int	i;
// 	int	fd_in;
// 	int	fd_out;

// 	i = 0;
// 	fd_in = 0;
// 	fd_out = 1;
// 	ft_dup2(in, 0);
// 	ft_dup2(out, 1);
// 	while (cmds->files && cmds->files[i])
// 	{
// 		if (cmds->files[i]->type == AMBIG)
// 			return (AMBIG_ERR);
// 		if (cmds->files[i]->type == IN_FILE)
// 			fd_in = open(cmds->files[i]->name, O_RDONLY, 0666);
// 		else if (cmds->files[i]->type == OUT_FILE && !is_directory(cmds->files[i]->name)) // ! You must print the error msg in this case
// 			fd_out = open(cmds->files[i]->name, O_CREAT | O_TRUNC | O_WRONLY, 0666);
// 		else if (cmds->files[i]->type == APPEND && !is_directory(cmds->files[i]->name))
// 			fd_out = open(cmds->files[i]->name, O_CREAT | O_APPEND | O_WRONLY, 0666);
// 		else
// 			fd_in = cmds->files[i]->fd;
// 		if (fd_in == -1 || fd_out == -1)
// 			return (NO_S_FILE);
// 		ft_dup2(fd_in, 0);
// 		ft_dup2(fd_out, 1);
// 		i++;
// 	}
// 	return (0);
// }
