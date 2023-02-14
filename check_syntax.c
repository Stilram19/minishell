/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 13:04:46 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/14 11:15:33 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special_char1(char c)
{
	if (c == '|' || c == '&'
		|| c == '<' || c == '>')
		return (1);
	return (0);
}

int	check_special_char(char *token, int boolean)
{
	int		count;
	char	reference;

	if (!is_special_char1(*token))
		return (0);
	count = 0;
	reference = *token;
	while (*(token + count) == reference)
		count++;
	if (count >= 3 || is_special_char1(*(token + count))
		|| (reference == '&' && count != 2))
		return (1);
	if (boolean && (reference != '<' && reference != '>'))
		return (1);
	return (0);
}

int	check_unclosed_quotes(char *token)
{
	int	ret;

	ret = 0;
	while (*token)
	{
		if (*token == '\'' || *token == '\"')
		{
			if (!ret)
				ret = *token;
			else if (ret == *token)
				ret = 0;
		}
		token++;
	}
	return (ret);
}

int	check_invalid_redirections(char **tokens)
{
	char	*token;

	while (*tokens)
	{
		token = *tokens;
		if (ft_strncmp(token, "<", 1)
			&& ft_strncmp(token, ">", 1) && tokens++)
			continue ;
		token = *(tokens + 1);
		if (!token || !(*token) || *token == '&'
			|| *token == '(' || *token == ')'
			|| *token == '#')
			return (1);
		tokens++;
	}
	return (0);
}

int	check_syntax(char **tokens)
{
	int	i;
	int	b;
	int	stop;

	i = 0;
	stop = 0;
	while (!stop && *(tokens + i))
	{
		b = (i == 0 || !(*(tokens + i + 1)));
		(stop || (stop = check_special_char(*(tokens + i), b)));
		(stop || (stop = check_unclosed_quotes(*(tokens + i))));
		i++;
	}
	(stop || (stop = check_invalid_redirections(tokens)));
	return (stop);
}
