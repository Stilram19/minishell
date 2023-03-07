/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:16:56 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/07 17:46:38 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		// TODO set exit status in env
		ft_putendl_fd("minishell: Syntax error!", 2);
		return (NULL);
	}
	new_line = ft_strdup(line);
	new_line = args_files_separation(new_line);
	printf("After rearrangement: %s\n", new_line);
	root = ft_garbage_collector(ALLOCATE, sizeof(t_node), NULL);
	parse_tree(new_line, root, 0);
	display_tree(root, 0);
	return (root);
}

void	main_task(char *line)
{
	t_node	*root;

	root = parsing(line);
	//if (!(g_global->exit_status))
		//execution(root);
	//TODO set exit status in env
	heredoc_clean(g_global->exit_status);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	char	*prompt;

	global_init(argc, argv, env);
	while (1)
	{
		prompt = get_prompt(g_global->exit_status);
		line = readline(prompt);
		if (!line)
			return (0);
		if (!(*line))
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
