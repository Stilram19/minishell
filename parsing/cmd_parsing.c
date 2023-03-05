/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:03:35 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/05 16:01:39 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
// var="ls -la"-->ls, -la
//expand --> split into tokens --> find cmd --> find arguments

void	wildcard_ambig_handler(char **args)
{
	int		quotes;
	char	*arg;

	while (*args)
	{
		quotes = 0;
		arg = *args;
		while (*arg)
		{
			open_close_quotes(*arg, &quotes);
			if (quotes && *arg == '*')
				*arg = WILDCARD_MASK;
			arg++;
		}
		args++;
	}
}

char	*wildcard_ambig(char *str)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (*(str + i))
	{
		open_close_quotes(*(str + i), &quotes);
		if (quotes && *(str + i) == '*')
			*(str + i) = WILDCARD_MASK;
		i++;
	}
	return (str);
}

void	quotes_handler(char **args)
{
	while (*args)
	{
		*args = remove_quotes(*args);
		unmask_quotes(*args);
		args++;
	}
	wildcard_ambig_handler(args);
}

void	cmd_parsing(t_node *root, char *str)
{
	char	**args;

	if (g->exit_status)
		return ;
	expand_if(&str);
	args = produce_tokens(str, mask_generation2(str));
	wildcard_ambig_handler(args);
	quotes_handler(args);
	root->data.cmd = *args;
	root->data.args = args;
}
