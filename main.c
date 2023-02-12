/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:49:06 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/12 18:51:17 by obednaou         ###   ########.fr       */
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
	char	*line;
	char	*mask;
	char	**tokens;

	(void)argc;
	(void)argv;
	get_env(env_dup(env));
	line = "echo $";
	mask = mask_generation(line);
	printf("%s\n", line);
	tokens = produce_tokens(line, mask);
	printf("%s\n", mask);
	ft_display_tokens(tokens);
	expanding(tokens);
	printf("After expanding:\n");
	ft_display_tokens(tokens);
	return (0);
}
