/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removing_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:35:28 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/13 11:27:45 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_and_update(char *add, int *open_quote_ptr)
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
	int		open_quote;

	while (*tokens)
	{
		i = 0;
		open_quote = 0;
		while (*(*tokens + i))
		{
			if ((*(*tokens + i) == '\'' || *(*tokens + i) == '\"')
				&& (open_quote == *(*tokens + i) || !open_quote))
				delete_and_update(*tokens + i, &open_quote);
			else
				i++;
		}
		tokens++;
	}
}
