/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:16:56 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/05 20:48:16 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		//node_init(root, 0);
	//	files_parsing(root, new_str);
		/*cmd_parsing(root, new_str);
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
		printf("}\n");*/
		/*while (i < root->data.f_count)
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
		}*/
		free(str);
	}
}

void	task(char *str)
{
	t_node	*root;

	root = ft_garbage_collector(ALLOCATE, sizeof(t_node), NULL);
	parse_tree(str, root, 0);
	display_tree(root, 0);
}

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
#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"
#define reset "\e[0m"

int c;
void	task1(char *str)
{
	if (syntax_test(str))
		c = 1;
	else
		c = 0;
}
//Regular text


int	main(int argc, char **argv, char **env)
{
	char	*line;
	char	*new_line;

	(void)argc;
	(void)argv;
	//test(env);
	restart();
	g->exit_status = EXIT_SUCCESS;
	get_env(env_dup(env));
	while (1)
	{
		const char* name;
		if (c == 0)
			name = GRN"➜"reset" minishell$ ";
		else
			name = RED"➜"reset" minishell$ ";
		line = readline(name);
		g->exit_status = EXIT_SUCCESS;
		//printf("%d\n", *line);
		if (!line)
			return (0);
		if (!(*line))
		{
			free(line);
			continue ;
		}
		add_history(line);
		new_line = ft_strdup(line);
		//task(new_line);
		task1(new_line);
		free(line);
		restart();
	}
	return (0);
}
