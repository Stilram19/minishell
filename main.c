/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:49:06 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/12 13:16:59 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "readline/readline.h"

void	ft_display_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (*(tokens + i))
	{
		printf("%s\n", *(tokens + i));
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
//	char	*line;
	//char	*mask;
//	char	**tokens;

	(void)argc;
	(void)argv;
	(void)env;
	//char **my_env = get_env(env_dup(env));
	/*while (1)
	{
		line = read_line("minishell$ ");
		add_hisory(line);
		free(line);
	}*/
	/*line = "ls>>a | echo \'ls > a\' &&\" hhhh\' || ls < a\"|\"";
	printf("%s\n", line);
	mask = mask_generation(line);
	printf("%s\n", mask);
	tokens = produce_tokens(line, mask);
	ft_display_tokens(tokens);*/
	function();
	//printf("%d\n", check_syntax(tokens));
	system("leaks minishell");
	return (0);
}
