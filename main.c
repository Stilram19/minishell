/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:49:06 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/10 17:06:24 by obednaou         ###   ########.fr       */
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

	/*while (1)
	{
		line = read_line("minishell$ ");
		add_hisory(line);
		free(line);
	}*/
	line = "ls>>>a | echo \'ls > a |\" hhhh\' ||| ls < a";
	mask = "00222012100001000000000000000012221001210";
	tokens = produce_tokens(line, mask);
	ft_display_tokens(tokens);
	return (0);
}
