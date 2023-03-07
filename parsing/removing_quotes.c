/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removing_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:35:28 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/07 18:22:26 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	*remove_quotes(char *str)
{
	int		i;
	char	*new_str;
	char	open_quote;

	i = 0;
	open_quote = 0;
	new_str = ft_strdup(str);
	while (*(new_str + i))
	{
		if ((*(new_str + i) == '\'' || *(new_str + i) == '\"')
			&& (open_quote == *(new_str + i) || !open_quote))
			delete_or_update(new_str + i, &open_quote);
		else
			i++;
	}
	return (new_str);
}
