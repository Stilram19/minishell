/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 13:04:46 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/17 14:51:46 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirect(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	check_meta_char(char *token)
{
	int		count;
	char	reference;

	if (!is_redirect(*token))
		return (0);
	count = 0;
	reference = *token;
	while (*(token + count) == reference)
		count++;
	if (count >= 3 || is_redirect(*(token + count)))
		return (1);
	return (0);
}

int	check_unclosed_quotes(char *token)
{
	int	ret;

	ret = 0;
	while (*token)
	{
		open_close_quotes(*token, &ret);
		token++;
	}
	return (ret);
}

//TODO regex of expected name after a redirection
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
	int	stop;

	i = 0;
	stop = 0;
	while (!stop && *(tokens + i))
	{
		(stop || (stop = check_meta_char(*(tokens + i))));
		(stop || (stop = check_unclosed_quotes(*(tokens + i))));
		i++;
	}
	//(stop || (stop = check_invalid_redirections(tokens)));
	return (stop);
}
