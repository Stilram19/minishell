/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:20:06 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/15 18:52:28 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_balance(char c, t_balance *b, char *brackets)
{
	int	b;

	b = 0;
	while (*brackets)
	{
		if (c == *brackets)
		{
			b = 1;
			break ;
		}
		brackets++;
	}
	if (!b)
		return ;
	if (b->top_i == -1 || c != b->stack[b->top_i])
	{
		b->top_i++;
		b->stack[b->top_i] = c;
		return ;
	}
	b->top_i--;
}

int	is_between_brackets(char *input_str)
{
	int			c;
	t_balance	b;
	char		*set;

	c = 0;
	b.top_i = -1;
	set = "()";
	b.stack = malloc(sizeof(char) * ft_strlen(input_str));
	while (*input_str)
	{
		c = 1;
		update_balance(*input_str, &b, set);
		input_str++;
	}
	free(b.stack);
	return (c && (b.top_i == -1));
}

int	is_command(char *input_str)
{
	int	ret;

	ret = 0;
	while (*input_str)
	{
		ret = 1;
		if (*input_str == '&' || *input_str == '|')
			return (0);
		input_str++;
	}
	return (ret);
}

int	is_operator(char *str)
{
	if ((*str == '&' && *(str + 1) == '&')
		|| *str == '|')
		return (1);
	return (0);
}

int	is_there_middle_operator(char *input_str)
{
	int			c;
	t_balance	b;
	char		*set;

	c = 0;
	b.top_i = -1;
	set = "\'\"()";
	b.stack = malloc(sizeof(ft_strlen(input_str)));
	while (*input_str)
	{
		update_balance(*input_str, &b, set);
		if (c && b.top_i == -1 && is_operator(input_str))
		{
			free(b.stack);
			return (1);
		}
		c = 1;
		input_str++;
	}
	free(b.stack);
	return (0);
}

char	*first_operand(char *str)
{
	int			i;
	int			c;
	char		*set;
	char		*ret;
	t_balance	b;

	c = 0;
	i = 0;
	set = "\'\"()";
	ret = ft_strdup(str);
	b.top_i = -1;
	b.stack = malloc(sizeof(char) * ft_strlen(ret));
	while (*(ret + i))
	{
		update_balance(*(ret + i), &b, set);
		if (c && b.top_i == -1 && is_operator(ret + i))
		{
			*(ret + i) == '\0';
			free(b.stack);
			return (ret);
		}
		i++;
		c = 1;
	}
	free(b.stack);
	return (ret);
}

char	*second_operand(char *str)
{
	int			i;
	int			c;
	char		*set;
	char		*ret;
	t_balance	b;

	c = 0;
	i = 0;
	b.top_i = -1;
	set = "\'\"()";
	b.stack = malloc(sizeof(char) * ft_strlen(str));
	while (*(str + i))
	{
		update_balance(*(str + i), &b, set);
		if (c && b.top_i == -1 && is_operator(ret + i))
		{
			ret = ft_strdup(str + i);
			free(b.stack);
			return (ret);
		}
		c = 1;
	}
	free(b.stack);
	return (ret);
}

int	second_statement_symbol(char *input_str)
{
	int	ret;

	ret = 0;
	if (is_command(input_str))
		return (check_command_syntax(input_str));
	if (is_between_brackets(input_str))
		return (second_statement_symbol(input_str));
	if (is_there_middle_operator(input_str))
	{
		ret = second_statement_symbol(first_operand(input_str));
		(ret || (ret = second_statement_symbol(second_operand(input_str))));
		return (ret);
	}
	return (1);
}

int	first_statement_symbol(char *input_str)
{
	if (!(*input_str))
		return (0);
	return (second_statement_symbol(input_str));
}
