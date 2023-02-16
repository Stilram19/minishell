/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:37:00 by okhiar            #+#    #+#             */
/*   Updated: 2023/02/15 21:16:31 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_dup2(int f1, int f2)
{
	// dprintf(2, "%d %d\n", f1, f2);
	if (f1 != f2)
	{
		if (dup2(f1, f2) == -1)
			perror("dup2");
		close(f1);
	}
}

int	get_flag(int x)
{
	static int flag;

	if (x >= 0)
		flag = x;
	return (flag);
}

int	exec_cmds(t_cmds *cmds, int in, int out)
{
	int	pid;
	int	status;

	pid = fork();
	if (!pid)
	{
		ft_dup2(in, 0);
		// printf("%p\n", cmds);
		ft_dup2(out, 1);
		if (ft_execvp(cmds->cmd, cmds->args))
			_ft_putstr_fd("\e[1;31mMinishell:\e[0m command not found\n", 2, 127);
	}
	if (get_flag(-1))
	{
		printf("%s\n", cmds->cmd);
		waitpid(pid, &status, 0);
		get_flag(0);
	}
	return (WEXITSTATUS(status));
}

int	execute(t_tree *root, int in, int out)
{
	int	fds[2];
	int	status;

	if (!root)
		return (0);
	if (root->operation == 0)
		return (exec_cmds(root->cmd, in, out));
	else
	{
		if (root->operation == PIPE)
		{
			// printf("I'm here\n");
			pipe(fds);
			execute(root->left, in, fds[1]);
			close(fds[1]);
			execute(root->right, fds[0], out);
			close(fds[0]);
		}
		else
		{
			get_flag(1);
			status = execute(root->left, in, out);
			if ((status != 0 && root->operation == AND_AND) \
				|| (status == 0 && root->operation == OR_OR))
			{
				printf("right one Will be skiped\n");
				return (status);
			}
			execute(root->right, in, out);
		}
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_tree *root;

	get_env(env_dup(env));
	root = new_node(PIPE, NULL);
	root->left = new_node(AND_AND, NULL);
	root->right = new_node(0, command_fill("wc", 0, 1));
	root->left->left = new_node(0, command_fill("ls", 0, 1));
	root->left->right = new_node(OR_OR, NULL);
	root->left->right->left = new_node(0, command_fill("pfhgwd", 0, 1));
	root->left->right->right = new_node(PIPE, NULL);
	root->left->right->right->left = new_node(0, command_fill("pwd", 0, 1));
	root->left->right->right->right = new_node(0, command_fill("wc", 0, 1));
	// root->left->right->right = new_node(0, command_fill("pwd", 0, 1));
	// printf("%p\n", root->left->left->cmd);
	execute(root, 0, 1);
	// sleep(50);
	(void)ac;
	(void)av;
}