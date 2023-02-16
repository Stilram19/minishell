/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:20:06 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/16 12:16:22 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_balance(char c, t_balance *b)
{
	if (c == '(' || c == ')')
	{
		if (b->top_i != -1 && c == ')' && b->stack[b->top_i] == '(')
		{
			b->top_i--;
			return ;
		}
		b->top_i++;
		b->stack[b->top_i] = c;
	}
}

void	open_close_quotes(char ch, int *c)
{
	if (ch == '\'' || ch == '\"')
	{
		if (*c == 0)
			*c = ch;
		else if (*c == ch)
			*c = 0;
	}
}

int	is_operator(char *str)
{
	if ((*str == '&' && *(str + 1) == '&')
		|| *str == '|')
		return (1);
	return (0);
}

/*int	check_brackets_balance(char *str)
{
	char		c;
	t_balance	b;

	c = 0;
	b.top_i = -1;
	b.stack = ft_garbage_collector(ALLOCATE, ft_strlen(str), NULL);
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			if (!c)
				c = *str;
			else if (c == *str)
				c = 0;
		}
		else if (!c)
			update_balance(*str, &b);
		str++;
	}
	return (b.top_i == -1);
}*/

int	is_between_brackets(char *str, int len)
{
	if (*str == '(' && *(str + len - 1) == ')')
		return (1);
	return (0);
}

int	is_command(char *str)
{
	int	c;
	int	ret;

	ret = 0;
	c = 0;
	while (*str)
	{
		ret = 1;
		open_close_quotes(*str, &c);
		if (!c && (*str == '&' || *str == '|'
				|| *str == '(' || *str == ')'))
			return (0);
		str++;
	}
	return (ret);
}


int	is_there_middle_operator(char *str, int len)// ! check there is no operator at the beginning
{
	int			c;
	t_balance	b;

	c = 0;
	b.top_i = -1;
	b.stack = ft_garbage_collector(ALLOCATE, len, NULL);
	while (*str)
	{
		open_close_quotes(*str, &c);
		update_balance(*str, &b);
		if (!c && b.top_i == -1 && is_operator(str))
			return (1);
		str++;
	}
	return (0);
}

char	*first_operand(char *str, int len)
{
	int			i;
	int			c;
	char		*ret;
	t_balance	b;

	c = 0;
	i = 0;
	b.top_i = -1;
	ret = ft_strdup(str);
	b.stack = ft_garbage_collector(ALLOCATE, len, NULL);
	while (*(ret + i))
	{
		open_close_quotes(*(ret + i), &c);
		if (!c)
			update_balance(*(ret + i), &b);
		if (!c && b.top_i == -1 && is_operator(ret + i))
		{
			*(ret + i) == '\0';
			return (ret);
		}
		i++;
	}
	return (ret);
}

char	*second_operand(char *str, int len)
{
	int			c;
	t_balance	b;

	c = 0;
	b.top_i = -1;
	b.stack = ft_garbage_collector(ALLOCATE, len, NULL);
	while (*str)
	{
		open_close_quotes(*str, &c);
		if (!c)
			update_balance(*str, &b);
		if (!c && b.top_i == -1 && is_operator(str))
		{
			((*str == '&') && (str++));
			break ;
		}
		str++;
	}
	return (str + 1);
}

int	second_statement_symbol(char *str, int len)
{
	int		ret;
	char	*new_str;

	ret = 0;
	if (is_command(str))
		return (check_command_syntax(str));
	if (is_between_brackets(str, len))
	{
		str++;
		*(str + len - 2) = '\0';
		return (second_statement_symbol(str, len - 2));
	}
	if (is_there_middle_operator(str, len))
	{
		new_str = first_operand(str, len);
		ret = second_statement_symbol(new_str, ft_strlen(new_str));
		(ret || (new_str = second_operand(str, len)));
		(ret || (ret = second_statement_symbol(new_str, ft_strlen(new_str))));
		return (ret);
	}
	return (1);
}

int	first_statement_symbol(char *input_str, int len)
{
	if (!len)
		return (0);
	return (second_statement_symbol(input_str, len));
}
