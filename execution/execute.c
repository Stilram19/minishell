/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:37:00 by okhiar            #+#    #+#             */
/*   Updated: 2023/03/04 21:30:33 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	io_cleanup(int in, int out)
{
	ft_dup2(in, 0);
	ft_dup2(out, 1);
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

int	buildins_brute_force(t_data *cmds, int flag)
{
	int	status;

	status = 0;
	if (!ft_strcmp(cmds->cmd, "cd"))
		status = ft_cd(cmds->args + 1);
	else if (!ft_strcmp(cmds->cmd, "env"))
		status = ft_env();
	else if (!ft_strcmp(cmds->cmd, "pwd"))
		status = ft_pwd();
	else if (!ft_strcmp(cmds->cmd, "echo"))
		status = ft_echo(cmds->args + 1);
	else if (!ft_strcmp(cmds->cmd, "export"))
		status = ft_export(cmds->args + 1);
	else if (!ft_strcmp(cmds->cmd, "unset"))
		status = ft_unset(cmds->args + 1);
	else if (!ft_strcmp(cmds->cmd, "exit"))
		status = ft_exit(cmds->args + 1, flag);
	return (status);
}

int	exec_buildin(t_data *cmds, int in, int out)
{
	int	status;
	int	tmp_io[2];

	tmp_io[0] = dup(0);
	tmp_io[1] = dup(1);
	printf("here\n");
	ft_dup2(in, 0);
	ft_dup2(out, 1);
	status = buildins_brute_force(cmds, 1);
	io_cleanup(tmp_io[0], tmp_io[1]);
	return (status);
}

int	exec_cmds(t_data *cmds, t_fdio in, t_fdio out)
{
	int	pid;
	int	status;

	if (is_buildin(cmds->cmd) && !cmds->status 
		&& defaults_io(in.type, out.type))
		return (exec_buildin(cmds, in.fd, out.fd));
	pid = fork();
	if (!pid)
	{
		sig_def();
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
		return (ft_putstr_fd("Minishell : No such file or directory\n", 2), 1);
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
	int	status;
	t_fdio	io_fd[2];

	io_fd[0].fd = STDIN_FILENO;
	io_fd[0].type = DFTERM;
	io_fd[1].fd = STDOUT_FILENO;
	io_fd[1].type = DFTERM;
	status = execute(root, io_fd[0], io_fd[1]);
	set_exit_status(status);
	return (status);
}
