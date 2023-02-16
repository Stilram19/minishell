/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   production_rules.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:22:12 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/16 20:10:58 by obednaou         ###   ########.fr       */
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

int	check_brackets_balance(char *str)
{
	int			i;
	int			c;
	int			a;
	t_balance	b;

	i = -1;
	c = 0;
	a = 0;
	b.top_i = -1;
	b.stack = ft_garbage_collector(ALLOCATE, ft_strlen(str), NULL);
	while (*(str + ++i))
	{
		open_close_quotes(*(str + i), &c);
		if (!c)
			update_balance(*(str + i), &b);
		(!a && (b.top_i != -1) && (a = 1));
		if (a && b.top_i == -1 && ++i)
			break ;
	}
	while (*(str + i) && *(str + i) != '(' && *(str + i) != ')')
		i++;
	return (!(*(str + i)));
}
//((asdf)(asdfa))&&((asdf))
int	is_between_brackets(char *str)
{
	int	i;
	int	c;
	int	ret;

	i = 0;
	c = 0;
	ret = 0;
	while (*(str + i) == ' ' || *(str + i) == '\t')
		i++;
	if (*(str + i) != '(')
		return (0);
	while (*(str + i))
	{
		open_close_quotes(*(str + i), &c);
		if (!c && *(str + i) == ')')
			ret = 1;
		else if (!c && *(str + i) != ' ' && *(str + i) != '\t')
			ret = 0;
		i++;
	}
	if (ret)
		return (check_brackets_balance(str));
	return (ret);
}
// ((ls || ls) && (ls || ls))
int	is_command(char *str)
{
	int	c;
	int	ret;

	ret = 0;
	c = 0;
	while (*str)
	{
		(!ret && (*str != ' ' && *str != '\t') && (ret = 1));
		open_close_quotes(*str, &c);
		if (!c && (*str == '&' || *str == '|'
				|| *str == '(' || *str == ')'))
			return (0);
		str++;
	}
	return (ret);
}

int	is_there_middle_operator(char *str)
{
	int			c;
	t_balance	b;

	c = 0;
	b.top_i = -1;
	while (*str == ' ' || *str == '\t')
		str++;
	if (is_operator(str))
		return (0);
	b.stack = ft_garbage_collector(ALLOCATE, ft_strlen(str), NULL);
	while (*str)
	{
		open_close_quotes(*str, &c);
		if (!c)
			update_balance(*str, &b);
		if (!c && b.top_i == -1 && is_operator(str))
			return (1);
		str++;
	}
	return (0);
}
//l|s
char	*first_operand(char *str)
{
	int			i;
	int			c;
	char		*ret;
	t_balance	b;

	c = 0;
	i = 0;
	b.top_i = -1;
	ret = ft_strdup(str);
	b.stack = ft_garbage_collector(ALLOCATE, ft_strlen(str), NULL);
	while (*(ret + i))
	{
		open_close_quotes(*(ret + i), &c);
		if (!c)
			update_balance(*(ret + i), &b);
		if (!c && b.top_i == -1 && is_operator(ret + i))
		{
			*(ret + i) = '\0';
			return (ret);
		}
		i++;
	}
	return (ret);
}

char	*second_operand(char *str)
{
	int			c;
	t_balance	b;

	c = 0;
	b.top_i = -1;
	b.stack = ft_garbage_collector(ALLOCATE, ft_strlen(str), NULL);
	while (*str)
	{
		open_close_quotes(*str, &c);
		if (!c)
			update_balance(*str, &b);
		if (!c && b.top_i == -1 && is_operator(str))
		{
			if (*str == '&' || (*str == '|' && *(str + 1) == '|'))
				str++;
			break ;
		}
		str++;
	}
	return (str + 1);
}

int	check_command_syntax(char *str)
{
	(void)str;
	return (0);
}

void	remove_outer_brackets(char **ptr_to_str)
{
	char	*str;

	str = *ptr_to_str;
	while (*str == ' ' || *str == '\t')
		str++;
	*ptr_to_str = str + 1;
	while (*str)
		str++;
	str--;
	while (*str == ' ' || *str == '\t')
		str--;
	*str = '\0';
}

int	second_production_rule(char *str)
{
	int		ret;
	char	*new_str;

	ret = 0;
	if (is_command(str))
		return (check_command_syntax(str));
	if (is_between_brackets(str))
	{
		remove_outer_brackets(&str);
		// printf("%s\n", str);
		return (second_production_rule(str));
	}
	if (is_there_middle_operator(str))
	{
		new_str = first_operand(str);
		ret = second_production_rule(new_str);
		(ret || (new_str = second_operand(str)));
		(ret || (ret = second_production_rule(new_str)));
		return (ret);
	}
	return (1);
}

int	first_production_rule(char *str)
{
	if (!(*str))
		return (0);
	return (second_production_rule(str));
}
//(ls || (-la))
//l|s