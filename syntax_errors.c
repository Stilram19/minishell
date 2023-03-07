/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 18:42:50 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/07 16:12:08 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
traverse the string and check:
(*) closed quotes.
(*) closed parenthesis

split with a new mask generation strategy into tokens
and traverse tokens from left to right:
(*) false operators. (e.g, |||, &|, <<<, >>>)
(*) before (): logical operator, pipe, or nothing.
(*) inside (): must not be blank (' ', '\0').
(*) after (): logical operator, pipe, or redirec
(only files, no arguments are allowed).
(*) logical operator and pipe: must not be the first, must not be the last.
(*) after redirec: a word (must not be blank).

(pwd && ls) | pwd ==> (pwd && ls), |, pwd
*/

int	operator_test(char **tokens, int i)
{
	char	*main_token;
	char	*left_token;
	char	*right_token;

	left_token = NULL;
	right_token = *(tokens + i + 1);
	((i) && (left_token = *(tokens + i - 1)));
	main_token = *(tokens + i);
	if (ft_strlen(main_token) >= 3)
		return (SYNTAX_ERROR);
	if (!right_token)
		return (SYNTAX_ERROR);
	if (ft_strchr("<>", *main_token))
	{
		if (is_meta(right_token))
			return (SYNTAX_ERROR);
		if (left_token && ft_strchr("<>", *left_token))
			return (SYNTAX_ERROR);
		return (VALID_SYNTAX);
	}
	if (!left_token)
		return (SYNTAX_ERROR);
	if (ft_strchr("&|", *right_token) || is_meta(left_token))
		return (SYNTAX_ERROR);
	return (VALID_SYNTAX);
}

int	is_argument_after_parenth(char **tokens)
{
	int		i;
	char	*token;

	i = 0;
	while (*(tokens + i))
	{
		token = *(tokens + i);
		if (!is_meta(token))
			return (SYNTAX_ERROR);
		if (*token != '<'
			&& *token != '>')
			break ;
		if (!(*(tokens + i + 1)))
			break ;
		i += 2;
	}
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
	if (right_token)
		return (is_argument_after_parenth(tokens + i + 1));
	return (VALID_SYNTAX);
	while (*main_token)
	{
		if (!ft_strchr("()", *main_token) && !is_blank(*main_token))
			return (VALID_SYNTAX);
		main_token++;
	}
	return (SYNTAX_ERROR);
}

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
	if (quotes || parenth)
		return (SYNTAX_ERROR);
	return (VALID_SYNTAX);
}

int	syntax_test(char *str)
{
	int		i;
	int		ret;
	char	**tokens;

	i = 0;
	ret = VALID_SYNTAX;
	if (preliminary_syntax_test(str))
		return (SYNTAX_ERROR);
	tokens = produce_tokens(str, mask_generation3(str, "<>&|"));
	while (!ret && *(tokens + i))
	{
		if (is_meta(*(tokens + i)))
			ret = operator_test(tokens, i);
		else if (ft_strchr(*(tokens + i), '(') == *(tokens + i))
		{
			ret = syntax_test(remove_outer_parenth2(*(tokens + i)));
			if (!ret)
				ret = parenth_test(tokens, i);
		}
		i++;
	}
	ft_garbage_collector(SINGLE_RELEASE, 0, str);
	ft_free(tokens);
	return (ret);
}
