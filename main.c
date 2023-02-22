/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:49:06 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/22 18:00:13 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_display_tokens(char **tokens)
{
	int	i;

	i = 0;
	printf("Tokens={");
	while (*(tokens + i))
	{
		printf("%s", *(tokens + i));
		if (*(tokens + ++i))
			printf(", ");
	}
	printf("}\n");
}

/*void task(char *line)
{
	char	*mask;
	char	**tokens;

	mask = mask_generation(line);
	printf("line: %s\n", line);
	tokens = produce_tokens(line, mask);
	printf("mask: %s\n", mask);
	ft_display_tokens(tokens);
	if (check_syntax(tokens))
	{
		printf("Syntax error\n");
	//	system("leaks minishell");
		return ;
	}
	expanding(tokens);
	printf("After expanding:\n");
	ft_display_tokens(tokens);
}*/

void	task(char *line)
{
	t_item	**items;

	items = items_classification(line);
	(void)items;
/*	while (*items)
	{
		if ((*items)->type == L_PARENTH)
			printf("(\n");
		else if ((*items)->type == R_PARENTH)
			printf(")\n");
		else if ((*items)->type == OR)
			printf("||\n");
		else if ((*items)->type == AND)
			printf("&&\n");
		else if ((*items)->type == PIPE)
			printf("|\n");
		else if ((*items)->type == OPERAND)
		{
			int	files_count;

			files_count = (*items)->operand->files_count;
			printf("OPERAND\n");
			printf("Files count = %d\n", (*items)->operand->files_count);
			printf("status=%d\n", (*items)->operand->status);
//			t_file	*files = (*items)->operand->files;
			while (files_count--)
			{
				if (files->file_type == IN)
					printf("IN\n");
				if (files->file_type == OUT)
					printf("OUT\n");
				if (files->file_type == APPEND)
					printf("APPEND\n");
				if (files->file_type == AMBIG_REDIREC)
					printf("AMBIG_REDIRECT\n");
				if (files->file_type == HEREDOC)
					printf("HEREDOC\n");
				files++;
			}
			while (files_count--)
			{
				printf("%s\n", files->name);
				files++;
			}
		}
	}*/
}

void	syntax(char *line)
{
	char	*str;

	str = ft_strdup(line);
	if (first_production_rule(str))
	{
		printf("Syntax error!\n");
		return ;
	}
	printf("Valid syntax\n");
}


int	main(int argc, char **argv, char **env)
{
	char	*line;

	(void)argc;
	(void)argv;
	get_env(env_dup(env));
	while (1)
	{
		sig_set();
		line = readline("minishell> ");
		if (!line)
			return (0);
		add_history(line);
		//syntax(line);
		task(line);
		free(line);
		ft_garbage_collector(GLOBAL_RELEASE, 0, NULL);
	}
	return (0);
}
