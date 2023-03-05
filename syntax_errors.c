/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 18:42:50 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/05 15:23:53 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// traverse the string and check:
// (*) closed quotes.
// (*) closed parenthesis

// split with a new mask generation strategy into tokens
// and traverse tokens from left to right:
// (*) false operators. (e.g, |||, &|, <<<, >>>)
// (*) before (): logical operator, pipe, or nothing.
// (*) inside (): must not be blank (' ', '\0').
// (*) after (): logical operator, pipe, or redirec (only files, no arguments are allowed).
// (*) logical operator and pipe: must not be the first, must not be the last.
// (*) after redirec: a word (must not be blank).

//(pwd && ls) | pwd ==> (pwd && ls), |, pwd

int	preliminary_syntax_test(char *str)
{
	int		quotes;
	int		parenth;

	quotes = 0;
	parenth = 0;
	while (*str)
	{
		open_close_quotes(*str, &quotes);
		if (quotes && str++)
			continue ;
		if (!parenth && *str == ')')
			return (SYNTAX_ERROR);
		open_close_parenth(*str, &parenth);
		str++;
	}
	return (quotes || parenth);
}

int	operator_test(char **tokens, int i)
{
	char	*token;

	token = *(tokens + i);
	if (*(tokens + i + 1) == NULL)
		return (SYNTAX_ERROR);
	if (ft_strlen(token) >= 3)
		return (SYNTAX_ERROR);
	if (ft_strchr(token, '>') || ft_strchr(token, '<'))
		return (VALID_SYNTAX);
	if (*token == '&' && *(token + 1) == '\0')
		return (SYNTAX_ERROR);
	if (*token == '<' || *token == '>')
		return (VALID_SYNTAX);
	if (i == 0)
		return (SYNTAX_ERROR);
	return (VALID_SYNTAX);
}

int	parenth_test(char **tokens, int i)
{
	char	*main_token;
	char	*left_token;
	char	*right_token;

	left_token = NULL;
	main_token = *(tokens + i);
	if (i)
		left_token = *(tokens + i - 1);
	right_token = *(tokens + i + 1);	
	if (left_token && ft_strchr("<>", *left_token))
		return (SYNTAX_ERROR);
	if (left_token && !is_meta(left_token))
		return (SYNTAX_ERROR);
	if (right_token && !is_meta(right_token))
		return (SYNTAX_ERROR);
	while (*main_token)
	{
		if (!ft_strchr("()", *main_token))
			return (VALID_SYNTAX);
		main_token++;
	}
	return (SYNTAX_ERROR);
}

void	ft_free(char **tokens)
{
	int	i;

	i = 0;
	while (*(tokens + i))
	{
		ft_garbage_collector(SINGLE_RELEASE, 0, *(tokens + i));
		i++;
	}
	ft_garbage_collector(SINGLE_RELEASE, 0, tokens);
}

int	syntax_test(char *str)
{
	int		i;
	int		ret;
	char	*tokens;

	i = 0;
	ret = 0;
	tokens = produce_tokens(str, mask_generation3(str));
	while (!ret && *(tokens + i))
	{
		if (is_meta(*(tokens + i)))
			ret = operator_test(tokens, i);
		else if (ft_strchr(*(tokens + i), '(') == *(tokens + i))
		{
			remove_outer_parenth(*(tokens + i));
			ret = syntax_test(*tokens);
			if (!ret)
				ret = parenth_test(tokens, i);
		}
		i++;
	}
	ft_free(tokens);
	return (ret);
}
