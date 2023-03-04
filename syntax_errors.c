/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 18:42:50 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/04 20:52:25 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// traverse the string and check:
// (*) closed quotes.
// (*) closed parenthesis.

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
		if (is_operator(*tokens))
			ret = operator_test(tokens, i);
		if (!ret && is_between_parenth(*tokens))
		{
			ret = syntax_test(*tokens);
			if (!ret)
				ret = parenth_test(tokens, i);
		}
		i++;
	}
	return (ret);
}

// mask generation 3:
// 1 space
// 2 &|<>
// 3 parenth