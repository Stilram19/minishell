/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removing_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:35:28 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/20 10:55:59 by obednaou         ###   ########.fr       */
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

char	*remove_quotes(char *token)
{
	int		i;
	char	*new_token;
	char	open_quote;

	i = 0;
	open_quote = 0;
	new_token = ft_strdup(token);
	while (*(new_token + i))
	{
		if ((*(new_token + i) == '\'' || *(new_token + i) == '\"')
			&& (open_quote == *(new_token + i) || !open_quote))
			delete_or_update(new_token + i, &open_quote);
		else
			i++;
	}
	return (new_token);
}
