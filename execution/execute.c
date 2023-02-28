/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:37:00 by okhiar            #+#    #+#             */
/*   Updated: 2023/02/28 14:08:30 by okhiar           ###   ########.fr       */
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

int	open_infile(t_files *files, int type)
{
	int	infile;

	if (type == HERE)
		return (files->fd);
	infile = open(files->name, O_RDONLY);
	return (infile);	
}

int	open_outfile(t_files *files, int type)
{
	int	outfile;

	if (type == APPEND)
		return (open(files->name, O_CREAT | O_APPEND| O_WRONLY, 0666));
	outfile = open(files->name, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	return (outfile);
}

int	*io_rect(t_files **files, int in, int out)
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
	while (files && *files)
	{
		if (files[i]->type == IN || files[i]->type == HERE)
		{
			if (tmp[0] != -1)
				close(io_fds[0]);
			io_fds[0] = open_infile(files[i], files[i]->type);
			tmp[0] = io_fds[0];
		}
		else if (files[i]->type == OUT || files[i]->type == APPEND)
		{
			if (tmp[1] != -1)
				close(io_fds[1]);
			io_fds[1] = open_outfile(files[i], files[i]->type);
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

// int	exec_buildin(t_operand *cmds, int in, int out)
// {
// 	int	status;
// 	int	tmp_io[2];

// 	tmp_io[0] = dup(0);
// 	tmp_io[1] = dup(1);
// 	status = redirect_io(cmds, in, out);
// 	if (status)
// 		return (io_cleanup(tmp_io[0], tmp_io[1]), redirect_error(status, 0));
// 	status = buildins_brute_force(cmds, 1);
// 	io_cleanup(tmp_io[0], tmp_io[1]);
// 	return (status);
// }

// int	exec_cmds(t_operand *cmds, int in, int out)
// {
// 	int	pid;
// 	int	tmp[2];
// 	int	status;

// 	if (is_buildin(cmds->cmd) && defaults_io(in, out)) // ! you must check every thing carefully ==> ls | (false || pwd && wc)
// 		return (exec_buildin(cmds, in, out));
// 	pid = fork();
// 	if (!pid)
// 	{
// 		printf("%s***%d\n", cmds->cmd, getpid());
// 		status = redirect_io(cmds, in, out);
// 		(status && redirect_error(status, 1));
// 		if (is_buildin(cmds->cmd))
// 			exit(buildins_brute_force(cmds, 0));
// 		if (ft_execvp(cmds->cmd, cmds->args))
// 			_ft_putstr_fd("\e[1;31mMinishell:\e[0m command not found\n", 2, 127);
// 	}
// 	waitpid(pid, &status, 0);
// 	return (WEXITSTATUS(status));
// }

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
	root = new_node(PIPE, NULL);
	// root->right = new_node(0, command_fill("cd", 0, 1));
	// root->right->cmd->args[0] = ft_strdup("/Users/okhihar");
	// root->right->cmd->args[1] = NULL;
	// // root->left->cmd->files[0] = (t_files *)malloc(sizeof(t_files));
	// // root->left->cmd->files[0]->type = IN_FILE;
	// // root->left->cmd->files[0]->name = ft_strdup("outfidfgle");
	// // root->left->cmd->files[1] = (t_files *)malloc(sizeof(t_files));
	// // root->left->cmd->files[1]->type = AMBIG;
	// // root->left->cmd->files[1]->name = ft_strdup("out1");
	// // root->left->cmd->files[2] = NULL;
	root->left = new_node(OPERAND, command_fill("ls", 0, 1));
	root->left->item->operand->args[0] = ft_strdup("ls");
	root->left->item->operand->args[1] = ft_strdup("-l");
	root->left->item->operand->args[2] = NULL;
	printf("here\n");
	root->left->item->operand->files[0] = malloc(sizeof(t_files));
	root->left->item->operand->files[0]->name = ft_strdup("dir");
	root->left->item->operand->files[0]->type = OUT_FILE;
	root->left->item->operand->files[1] = NULL;
	root->right = new_node(OPERAND, command_fill("pwd", 0, 1));
	root->right->item->operand->args[0] = ft_strdup("pwd");
	// root->right->item->operand->args[1] = ft_strdup("15");
	// root->right->item->operand->args[2] = ft_strdup("");
	root->right->item->operand->args[1] = NULL;
	// root->right->cmd->args[0] = ft_strdup("head");
	// root->right->cmd->args[1] = ft_strdup("-n5");
	// root->right->cmd->args[2] = NULL;
	// root->right->left = new_node(0, command_fill("sleep", 0, 1));
	// root->right->left->cmd->args[1] = ft_strdup("5");
	// root->right->left->cmd->args[2] = NULL;
	// root->right->right = new_node(PIPE, NULL);
	// root->right->right->left = new_node(0, command_fill("sleep", 0, 1));
	// root->right->right->left->cmd->args[1] = ft_strdup("3");
	// root->right->right->left->cmd->args[2] = NULL;
	// root->right->right->right = new_node(0, command_fill("pwd", 0, 1));
	
	// root->left = new_node(0, command_fill("ls", 0, 1));
	// root->right = new_node(OR_OR, NULL);
	// root->right->left = new_node(0, command_fill("lgser", 0, 1));
	// root->right->right = new_node(AND_AND, NULL);
	// root->right->right->left = new_node(0, command_fill("pwd", 0, 1));
	// root->right->right->right = new_node(0, command_fill("wc", 0, 1));
	// printf("%p\n", root->operand->args);
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
	printf("here %d %s\n", status, get_var_value("?"));
	// sleep(20);
	return (status);
}