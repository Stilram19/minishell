/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:16:56 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/02 11:56:54 by obednaou         ###   ########.fr       */
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
	get_env(env_dup(env));
	root = ft_garbage_collector(ALLOCATE, sizeof(t_node), NULL);
	while (1)
	{
		i = 0;
		str = readline("$ ");
		if (!str)
			return ;
		add_history(str);
		char *new_str;
		new_str = ft_strdup(str);
		//restart(env);
		//node_init(root, 0);
		files_parsing(root, str);
		while (i < root->data.f_count)
		{
			if ((root->data.files)[i].type == IN)
				printf("IN|%p\n", (root->data.files)[i].pathname);
			else if ((root->data.files)[i].type == OUT)
				printf("OUT|%p\n", (root->data.files)[i].pathname);
			else if ((root->data.files)[i].type == APPEND)
				printf("APPEND|%p\n", (root->data.files)[i].pathname);
			else if ((root->data.files)[i].type == HERE)
				printf("HERE|%p\n", (root->data.files)[i].pathname);
			else if ((root->data.files)[i].type == AMBIG)
				printf("AMBIG\n");
			else
				printf("NOT DETECTED\n");
			i++;
		}
		free(new_str);
		free(str);
	}
}
//(ls && pwd || pwd)
int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	test(env);
	return (0);
}
