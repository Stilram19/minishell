/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:16:56 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/06 18:04:02 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*first_operator(char *str);
int		operator_type(char *op);

/*void	test(void)
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
		//node_init(root, 0);
	//	files_parsing(root, new_str);
		cmd_parsing(root, new_str);
		printf("cmd: {%s}\n", root->data.cmd);
		char	**args;

		args = root->data.args;
		printf("args: {");
		while (*args)
		{
			printf("%s", *args);
			if (*(args + 1))
				printf(", ");
			args++;
		}
		printf("}\n");
		while (i < root->data.f_count)
		{
			if ((root->data.files)[i].type == IN)
				printf("IN|%s\n", (root->data.files)[i].pathname);
			else if ((root->data.files)[i].type == OUT)
				printf("OUT|%s\n", (root->data.files)[i].pathname);
			else if ((root->data.files)[i].type == APPEND)
				printf("APPEND|%s\n", (root->data.files)[i].pathname);
			else if ((root->data.files)[i].type == HERE)
				printf("HERE|%s\n", (root->data.files)[i].pathname);
			else if ((root->data.files)[i].type == AMBIG)
				printf("AMBIG\n");
			else
				printf("NOT DETECTED\n");
			i++;
		}
		free(str);
	}
}*/

/*void	task(char *str)
{
	t_node	*root;

	root = ft_garbage_collector(ALLOCATE, sizeof(t_node), NULL);
	parse_tree(str, root, 0);
	display_tree(root, 0);
}*/

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

void	task(char *line)
{
	char	*new_line;

	g->exit_status = EXIT_SUCCESS;
	new_line = ft_strdup(line);
	/*g->exit_status = syntax_test(new_line);
	if (g->exit_status)
	{
		// set exit status in env
		ft_putendl_fd("minishell: Syntax error!", 2);
		return ;
	}*/
	//new_line = args_files_separation(new_line);
	//printf("After rearrangement: %s\n", new_line);
 	/*char *mask;
 	char	**tokens;

 	mask = mask_generation3(new_line, "<>&|");
 	tokens = produce_tokens(new_line, mask);
 	ft_display(tokens);*/
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	char	*prompt;

	global_init(argc, argv, env);
	while (1)
	{
		prompt = get_prompt(g->exit_status);
		line = readline(prompt);
		if (!line)
			return (0);
		if (!(*line))
		{
			free(line);
			continue ;
		}
		add_history(line);
		task(line);
		refresh(line);
	}
	return (0);
}
