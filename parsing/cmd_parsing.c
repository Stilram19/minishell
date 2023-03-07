/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:03:35 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/07 18:22:26 by okhiar           ###   ########.fr       */
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

	if (g_global->exit_status)
		return ;
	expand_if(&str);
	args = produce_tokens(str, mask_generation2(str));
	wildcard_ambig_handler(args);
	quotes_handler(args);
	root->data.cmd = *args;
	root->data.args = args;
}
