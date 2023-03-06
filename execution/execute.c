/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:37:00 by okhiar            #+#    #+#             */
/*   Updated: 2023/03/06 16:25:55 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child_sig(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		exit(42);// ! will checked
	}
}

int	exec_cmds(t_data *cmds, t_fdio in, t_fdio out)
{
	int	pid;
	int	status;

	cmds->args = wildcards_slice(cmds->args);
	cmds->cmd = cmds->args[0];
	if (is_buildin(cmds->cmd) && !cmds->status
		&& defaults_io(in.type, out.type))
		return (exec_buildin(cmds, in.fd, out.fd));
	pid = fork();
	signal(SIGINT, SIG_IGN);
	if (!pid)
	{
		sig_def();
		signal(SIGINT, child_sig);
		ft_dup2(in.fd, 0);
		ft_dup2(out.fd, 1);
		if (is_buildin(cmds->cmd))
			exit(buildins_brute_force(cmds, 0));
		if (ft_execvp(cmds->cmd, cmds->args))
			_ft_putstr_fd("\e[1;31mMinishell:\e[0m command not found\n", 2, 127);
	}
	waitpid(pid, &status, 0);
	status = check_exit_reason(status);
	return (status);
}

int	pipe_nodes(t_node *root, t_fdio in, t_fdio out)
{
	int		pid;
	int		status;
	t_fdio	*fd_io;
	int		fds[2];

	pipe(fds);
	fd_io = set_io_type(fds, PIPE_IO);
	pid = fork();
	if (!pid)
	{
		close(fds[0]);
		status = execute(root->left, in, fd_io[1]);
		close(fds[1]);
		exit(status);
	}
	close(fds[1]);
	// if (in.fd != STDIN_FILENO)
	// 	close(in.fd); // ! will be validated
	status = execute(root->right, fd_io[0], out);
	close(fds[0]);
	waitpid(pid, 0, 0);
	return (status);
}

int	redirect_io_node(t_node *root, t_fdio in, t_fdio out)
{
	t_fdio	*io_fd;
	int		status;

	io_fd = io_rect(&root->data, in, out);
	if (!io_fd)
		return (1);
	status = execute(root->left, io_fd[0], io_fd[1]);
	if (io_fd[0].fd != in.fd)
		close(io_fd[0].fd);
	if (io_fd[1].fd != out.fd)
		close(io_fd[1].fd);
	return (status);
}

int	execute(t_node *root, t_fdio in, t_fdio out)
{
	int	status;

	if (root->data.type == COMMAND)
	{
		if (!root->data.cmd)
			return (0);
		return (exec_cmds(&root->data, in, out));
	}
	if (root->data.type == PIPE)
		return (pipe_nodes(root, in, out));
	if (root->data.type == REDIREC)
		return (redirect_io_node(root, in, out));
	status = execute(root->left, in, out);
	if ((status != 0 && root->data.type == AND) \
		|| (status == 0 && root->data.type == OR))
		return (status);
	status = execute(root->right, in, out);
	return (status);
}

int	exec_line(t_node *root)
{
	int		status;
	t_fdio	io_fd[2];

	io_fd[0].fd = STDIN_FILENO;
	io_fd[0].type = DFTERM;
	io_fd[1].fd = STDOUT_FILENO;
	io_fd[1].type = DFTERM;
	status = execute(root, io_fd[0], io_fd[1]);
	set_exit_status(status);
	return (status);
}
