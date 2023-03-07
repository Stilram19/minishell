/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:16:56 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/07 15:44:24 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*first_operator(char *str);
int		operator_type(char *op);

void	test(void)
{
	int		i;
	char	*str;
	t_node	*root;

	i = 0;
	//get_env(env_dup(env));
	while (1)
	{
		i = 0;
		str = readline("$ ");
		if (!str)
		{
			//system("leaks minishell");
			return ;
		}
		add_history(str);
		char *new_str;

		restart();
		g->exit_status = 0;
		new_str = ft_strdup(str);
		root = ft_garbage_collector(ALLOCATE, sizeof(t_node), NULL);
		parse_tree(new_str, root, 0);
		free(str);
	}
}

void	task(char *str)
{
	t_node	*root;

	root = ft_garbage_collector(ALLOCATE, sizeof(t_node), NULL);
	parse_tree(str, root, 0);
	// printf("%p\n", root->data.cmd);
	// display_tree(root, 0);
	exec_line(root);
	// ft_env();
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	char	*new_line;

	(void)argc;
	(void)argv;
	// restart();
	init_session();
	g->exit_status = EXIT_SUCCESS;
	get_env(env_dup(env));
	while (1)
	{
		line = readline("\e[1;33m➥\e[0m \e[1;36mMinishell> \e[0m");
		if (!line)
			return (0);
		if (!(*line))
		{
			free(line);
			continue ;
		}
		add_history(line);
		new_line = ft_strdup(line);
		task(new_line);
		free(line);
		restart();
		g->exit_status = EXIT_SUCCESS;
	}
	return (0);
}
