/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:37:00 by okhiar            #+#    #+#             */
/*   Updated: 2023/03/09 02:44:37 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pipe_nodes(t_node *root, t_fdio in, t_fdio out)
{
	int		pid;
	int		status;
	int		left_status;
	t_fdio	*fd_io;
	int		fds[2];

	pipe(fds);
	fd_io = set_io_type(fds, C_EXEC);
	pid = fork();
	if (!pid)
	{
		close(fds[0]);
		status = check_subshell(root->left, in, fd_io[1], root->data.status);
		close(fds[1]);
		exit(status);
	}
	close(fds[1]);
	// (in.type == C_EXEC && close(in.fd));
	if (in.type == C_EXEC) {
		close(in.fd);
	}
	status = check_subshell(root->right, fd_io[0], out, root->data.status);
	close(fds[0]);
	waitpid(pid, &left_status, 0);
	if (is_signaled(left_status))
		g_global->sig_flag = 1;
	return (status);
}

int	redirect_io_node(t_node *root, t_fdio in, t_fdio out)
{
	t_fdio	*io_fd;
	int		status;

	io_fd = io_rect(&root->data, in, out);
	if (!io_fd)
		return (1);
	status = check_subshell(root->left, io_fd[0], io_fd[1], root->data.status);
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
	status = check_subshell(root->left, in, out, root->data.status);
	if ((status != 0 && root->data.type == AND) \
		|| (status == 0 && root->data.type == OR))
		return (status);
	status = check_subshell(root->right, in, out, root->data.status);
	return (status);
}

int	check_subshell(t_node *root, t_fdio in, t_fdio out, int level)
{
	int	pid;
	int	status;

	if (level == root->data.status)
		return (execute(root, in, out));
	pid = fork();
	signal(SIGINT, SIG_IGN);
	if (!pid && io_subs_type(&in, &out))
		exit(execute(root, in, out));
	waitpid(pid, &status, 0);
	status = check_exit_reason(status);
	return (status);
}

int	execution(t_node *root)
{
	int		status;
	t_fdio	io_fd[2];

	set_exit_status(EXIT_SUCCESS);
	io_fd[0].fd = STDIN_FILENO;
	io_fd[0].type = P_EXEC;
	io_fd[1].fd = STDOUT_FILENO;
	io_fd[1].type = P_EXEC;
	status = check_subshell(root, io_fd[0], io_fd[1], 0);
	g_global->exit_status = status;
	if (g_global->sig_flag)
		write(2, "\n", 1);
	return (status);
}
