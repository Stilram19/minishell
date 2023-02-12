/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 18:21:19 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/12 14:01:07 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// first encountered character in the list {', ", $}
// if ' is the first encountered character, then no expanding happens.
// if " or $ is the first encountered character, then it may expand.
// skip every charcter before $
// go through characters after $, until you find a non-apha-numeric character{'\0', $, "} are included.
// if '\0' is directely after $, don't expand, let things as it is.
// otherwise look for the variable found between $ and the first encountered non-alpha-numeric character.
// Reallocate for this token, and keep every character before $, and here:
// if you find the variable then substitute it with its value.
// otherwise skip it (as if nothing existed before).

char	first_encountered(char *token)
{
	char	ret;

	ret = 0;
	while (*token)
	{
		if (*token == '\'' || *token == '\"' || *token == '$')
		{
			ret = *token;
			break ;
		}
		token++;
	}
	return (ret);
}

char	*var_expand(char *token)
{

}

void	expand_if(char **tokens, int index)
{
	int		i;
	char	*token;

	i = 0;
	token = *(tokens + index);
	if (first_encountered(token) == '\'')
		return ;
	while (*(token + i))
	{
		while (*(token + i) != '$')
			i++;
		if (*(token + i + 1) != '?' && !is_alpha(*(token + i + 1)) && ++i)
			continue ;
		token = var_expand(tokens, index, var_len(token + i));
	}
}

void	expanding(char **tokens)
{
	int		i;
	char	**my_env;

	i = 0;
	my_env = get_env(NULL);
	while (*(tokens + i))
	{
		if (strchr(*(tokens + i), '$')
			expand_if(tokens, i);
		i++;
	}
}
