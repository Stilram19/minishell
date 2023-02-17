/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:37:00 by okhiar            #+#    #+#             */
/*   Updated: 2023/02/17 18:48:25 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "build-ins/buildins.h"

void	ft_dup2(int f1, int f2)
{
	// dprintf(2, "%d %d %d\n", f1, f2, getpid());
	if (f1 != f2)
	{
		if (dup2(f1, f2) == -1)
			perror("dup2");
		close(f1);
	}
}

void	io_cleanup(int in, int out)
{
	ft_dup2(in, 0);
	ft_dup2(out, 1);
}

int	execute_buildin(t_cmds *cmds)
{
	int	status;

	status = 0;
	if (!ft_strcmp(cmds->cmd, "cd"))
		status = ft_cd(cmds->args[1]);
	else if (!ft_strcmp(cmds->cmd, "env"))
		status = ft_env();
	else if (!ft_strcmp(cmds->cmd, "pwd"))
		status = ft_pwd();
	else if (!ft_strcmp(cmds->cmd, "echo"))
		status = ft_echo(cmds->args + 1);
	else if (!ft_strcmp(cmds->cmd, "export"))
		status = ft_export(cmds->args);
	else if (!ft_strcmp(cmds->cmd, "unset"))
		status = ft_unset(cmds->args);
	else if (!ft_strcmp(cmds->cmd, "exit"))
		status = ft_exit(cmds->args);
	return (status);
}

void	redirect_io(t_cmds *cmds, int in, int out)
{
	int	i;
	int	fd_in;
	int	fd_out;

	i = 0;
	fd_in = 0;
	fd_out = 1;
	ft_dup2(in, 0);
	ft_dup2(out, 1);
	while (cmds->files && cmds->files[i])
	{
		if (cmds->files[i]->type == IN_FILE)
			fd_in = open(cmds->files[i]->name, O_RDONLY, 0666);
		else if (cmds->files[i]->type == OUT_FILE)
			fd_out = open(cmds->files[i]->name, O_CREAT | O_TRUNC | O_WRONLY, 0666);
		else
			fd_in = cmds->files[i]->fd;
		if (fd_in == -1)
			_ft_putstr_fd("\e[1;31mMinishell:\e[0m file not found\n", 2, 1);
		ft_dup2(fd_in, 0);
		ft_dup2(fd_out, 1);
		i++;
	}
}

int	exec_cmds(t_cmds *cmds, int in, int out)
{
	int	pid;
	int	status;

	if (is_buildin(cmds->cmd))
	{
		redirect_io(cmds, in, out);
		status = execute_buildin(cmds);
		return (status);
	}
	pid = fork();
	if (!pid)
	{
		printf("%s***\n", cmds->cmd);
		redirect_io(cmds, in, out);
		if (ft_execvp(cmds->cmd, cmds->args))
			_ft_putstr_fd("\e[1;31mMinishell:\e[0m command not found\n", 2, 127);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

int	pipe_nodes(t_tree *root, int in, int out)
{
	int	pid;
	int	status;
	int	fds[2];

	pipe(fds);
	pid = fork();
	if (!pid)
	{
		close(fds[0]);
		status = execute(root->left, in, fds[1]);
		close(fds[1]);
		exit(status);
	}
	close(fds[1]);
	status = execute(root->right, fds[0], out);
	close(fds[0]);
	waitpid(pid, 0, 0);
	return (status);
}

int	execute(t_tree *root, int in, int out)
{
	int	status;

	if (root->operation == 0) // ! BASE CASE
		return (exec_cmds(root->cmd, in, out));
	if (root->operation == PIPE)
	{
		status = pipe_nodes(root, in, out);
		return (status);
	}
	else
	{
		status = execute(root->left, in, out);
		if ((status != 0 && root->operation == AND_AND) \
			|| (status == 0 && root->operation == OR_OR))
			return (status);
		status = execute(root->right, in, out);
		return (status);
	}
	return (0);
}

int	exec_line(t_tree *root)
{
	int	tmp_in;
	int	tmp_out;
	int	status;
	
	tmp_in = dup(0);
	tmp_out = dup(1);
	status = execute(root, 0, 1);
	io_cleanup(tmp_in, tmp_out);
	return (status);
}

int	main(int ac, char **av, char **env)
{
	t_tree *root;
	int		status;
	int		lstatus;

	get_env(env_dup(env));
	root = new_node(AND_AND, NULL);
	root->left = new_node(0, command_fill("ls", 0, 1));
	// root->left->cmd->files[0] = (t_files *)malloc(sizeof(t_files));
	// root->left->cmd->files[0]->type = IN_FILE;
	// root->left->cmd->files[0]->name = ft_strdup("outfidfgle");
	// root->left->cmd->files[1] = (t_files *)malloc(sizeof(t_files));
	// root->left->cmd->files[1]->type = IN_FILE;
	// root->left->cmd->files[1]->name = ft_strdup("out1");
	// root->left->cmd->files[2] = NULL;
	root->right = new_node(0, command_fill("echo", 0, 1));
	root->right->cmd->args[1] = ft_strdup("Hello World");
	root->right->cmd->args[2] = NULL;
	root->right->cmd->files[0] = (t_files *)malloc(sizeof(t_files));
	root->right->cmd->files[0]->type = OUT_FILE;
	root->right->cmd->files[0]->name = ft_strdup("out2");
	root->right->cmd->files[1] = NULL;
	// root->right->left = new_node(0, command_fill("sleep", 0, 1));
	// root->right->left->cmd->args[1] = ft_strdup("5");
	// root->right->left->cmd->args[2] = NULL;
	// root->right->right = new_node(PIPE, NULL);
	// root->right->right->left = new_node(0, command_fill("sleep", 0, 1));
	// root->right->right->left->cmd->args[1] = ft_strdup("3");
	// root->right->right->left->cmd->args[2] = NULL;
	// root->right->right->right = new_node(0, command_fill("pwd", 0, 1));
	// root->left = new_node(AND_AND, NULL);
	// root->right = new_node(0, command_fill("wc", 0, 1));
	// root->left->left = new_node(0, command_fill("ls", 0, 1));
	// root->left->right = new_node(OR_OR, NULL);
	// root->left->right->left = new_node(0, command_fill("pfhgwd", 0, 1));
	// root->left->right->right = new_node(PIPE, NULL);
	// root->left->right->right->left = new_node(0, command_fill("sleep", 0, 1));
	// root->left->right->right->left->cmd->args[1] = ft_strdup("3");
	// root->left->right->right->left->cmd->args[2] = NULL;
	// root->left->right->right->right = new_node(0, command_fill("wc", 0, 1));
	status = exec_line(root);
	// sleep(50);
	// int i = -1;
	// while (++i < 4)
	// 	if (waitpid(-1, &status, 0) == root->right->right->right->cmd->pid)
	// 		lstatus = WEXITSTATUS(status);
	// waitpid(pid1, &status, 0);
	// sleep(30);
	(void)ac;
	(void)av;
	sleep(20);
	printf("here\n");
	return (status);
}