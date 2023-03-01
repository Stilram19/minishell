/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:37:00 by okhiar            #+#    #+#             */
/*   Updated: 2023/02/28 15:31:55 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_dup2(int f1, int f2)
{
	if (f1 == f2)
		return ;
	if (dup2(f1, f2) == -1)
		perror("dup2");
	close(f1);
}

int	defaults_io(int in, int out)
{
	if (in == 0 && out == 1)
		return (1);
	return (0);
}

void	io_cleanup(int in, int out)
{
	ft_dup2(in, 0);
	ft_dup2(out, 1);
}

int	buildins_brute_force(t_operand *cmds, int flag)
{
	int	status;

	status = 0;
	if (!ft_strcmp(cmds->cmd, "cd"))
		status = ft_cd(cmds->args);
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
		status = ft_exit(cmds->args + 1, flag);
	return (status);
}

int	exec_cmds(t_operand *cmds, int in, int out)
{
	int	pid;
	int	tmp[2];
	int	status;

	// if (is_buildin(cmds->cmd) && defaults_io(in, out)) // ! you must check every thing carefully ==> ls | (false || pwd && wc)
	// 	return (exec_buildin(cmds, in, out));
	pid = fork();
	if (!pid)
	{
		printf("%s***%d\n", cmds->cmd, getpid());
		ft_dup2(in, 0);
		ft_dup2(out, 1);
		if (is_buildin(cmds->cmd))
			exit(buildins_brute_force(cmds, 0));
		if (ft_execvp(cmds->cmd, cmds->args))
			_ft_putstr_fd("\e[1;31mMinishell:\e[0m command not found\n", 2, 127);
	}
	if (in != 0)
		close(in);
	if (out != 1)
		close(out);
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

int	redirect_io_node(t_tree *root, int in, int out)
{
	int	*io_fd;
	int	status;

	io_fd = io_rect(root->item->files, in, out); // ! if NULL Returned then return here
	if (!io_fd)
		return (ft_putstr_fd("Minishell : No such file or directory\n", 2), 1);
	status = execute(root->left, io_fd[0], io_fd[1]);
	return (status);
}

int	execute(t_tree *root, int in, int out)
{
	int	status;
	int	pid;

	if (root->item->type == COMMAND) // ! BASE CASE
		return (exec_cmds(root->item->operand, in, out));
	if (root->item->type == PIPE)
		return (pipe_nodes(root, in, out));
	if (root->item->type == REDIREC)
		return (redirect_io_node(root, in, out));
	status = execute(root->left, in, out);
	if ((status != 0 && root->item->type == AND) \
		|| (status == 0 && root->item->type == OR))
		return (status);
	status = execute(root->right, in, out);
	return (status);
}

int	exec_line(t_tree *root)
{
	// int	tmp_in;
	// int	tmp_out;
	int	status;

	// tmp_in = dup(0);
	// tmp_out = dup(1);
	// io_cleanup(0, 1);
	status = execute(root, STDIN_FILENO, STDOUT_FILENO);
	set_exit_status(status);
	return (status);
}

int	main(int ac, char **av, char **env)
{
	t_tree *root;
	int		status;
	int		lstatus;

	get_env(env_dup(env));
	root = new_node(REDIREC, NULL, files_fill());
	root->item->files[0] = (t_files *)malloc(sizeof(t_files));
	root->item->files[0]->name = "out";
	root->item->files[0]->type = OUT;
	root->item->files[1] = (t_files *)malloc(sizeof(t_files));
	root->item->files[1]->name = "notfound";
	root->item->files[1]->type = IN;
	root->item->files[2] = NULL;
	root->left = new_node(COMMAND, command_fill("ls"), NULL);
	status = exec_line(root);
	(void)ac;
	(void)av;
	printf("here %d %s\n", status, get_var_value("?"));
	sleep(20);
	return (status);
}