/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:49:06 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/16 18:04:28 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "readline/readline.h"

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

void task(char *line)
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
	remove_quotes(tokens);
	printf("After removing quotes\n");
	ft_display_tokens(tokens);
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
		line = readline("minishell> ");
		//task(line);
		syntax(line);
		add_history(line);
		free(line);
		//system("leaks minishell");
	}
	return (0);
}
