/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removing_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:35:28 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/18 14:59:28 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_or_update(char *add, char *open_quote_ptr)
{
	if (!(*open_quote_ptr))
		*open_quote_ptr = *add;
	else if (*open_quote_ptr == *add)
		*open_quote_ptr = 0;
	while (*add)
	{
		*add = *(add + 1);
		add++;
	}
}

void	remove_quotes(char **tokens)
{
	int		i;
	char	open_quote;

	while (*tokens)
	{
		i = 0;
		open_quote = 0;
		while (*(*tokens + i))
		{
			if ((*(*tokens + i) == '\'' || *(*tokens + i) == '\"')
				&& (open_quote == *(*tokens + i) || !open_quote))
				delete_or_update(*tokens + i, &open_quote);
			else
				i++;
		}
		tokens++;
	}
}
