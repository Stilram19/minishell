/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:16:56 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/09 01:34:24 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// declaring it once for all the app, to prevent liking issues
t_global	*g_global;

void	ft_display(char **tokens)
{
	printf("tokens: {");
	while (*tokens)
	{
		printf("%s", *tokens);
		if (++tokens && *tokens)
			printf(", ");
	}
	printf("}\n");
}

t_node	*parsing(char *line)
{
	char	*new_line;
	t_node	*root;

	root = NULL;
	g_global->exit_status = EXIT_SUCCESS;
	new_line = ft_strdup(line);
	g_global->exit_status = syntax_test(new_line);
	if (g_global->exit_status)
	{
		ft_putendl_fd("minishell: Syntax error!", 2);
		return (NULL);
	}
	new_line = ft_strdup(line);
	new_line = args_files_separation(new_line);
	root = ft_garbage_collector(ALLOCATE, sizeof(t_node), NULL);
	parse_tree(new_line, root, 0);
	return (root);
}

void	main_task(char *line)
{
	t_node	*root;

	root = parsing(line);
	if (!(g_global->exit_status))
		execution(root);
	set_exit_status(g_global->exit_status);
	heredoc_clean(g_global->exit_status);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	char	*prompt;

	global_init(argc, argv, env);
	while (1)
	{
		sig_set();
		prompt = get_prompt(g_global->exit_status);
		line = readline(prompt);
		if (!line)
		{
			printf("exit\n");
			return (0);
		}
		if (is_all_blank(line))
		{
			free(line);
			continue ;
		}
		add_history(line);
		main_task(line);
		refresh(line);
	}
	return (0);
}
