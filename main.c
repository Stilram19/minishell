/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:16:56 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/02 19:07:06 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*first_operator(char *str);
int		operator_type(char *op);

void	test(char **env)
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

		restart(env);
		g->exit_status = 0;
		new_str = ft_strdup(str);
		root = ft_garbage_collector(ALLOCATE, sizeof(t_node), NULL);
		//node_init(root, 0);
		//files_parsing(root, new_str);
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

//(ls && pwd || pwd)
int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	test(env);

	return (0);
}
