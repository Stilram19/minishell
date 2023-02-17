/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   production_rules3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:27:12 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/17 11:39:16 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_there_middle_operator(char *str)
{
	int			c;
	t_balance	b;

	c = 0;
	b.top_i = -1;
	while (is_blank(*str))
		str++;
	if (fourth_production_rule(str))
		return (0);
	b.stack = ft_garbage_collector(ALLOCATE, ft_strlen(str), NULL);
	while (*str)
	{
		open_close_quotes(*str, &c);
		if (!c)
			update_balance(*str, &b);
		if (!c && b.top_i == -1 && fourth_production_rule(str))
			return (1);
		str++;
	}
	return (0);
}

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
		if (!c && b.top_i == -1 && fourth_production_rule(ret + i))
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
		if (!c && b.top_i == -1 && frouth_production_rule(str))
		{
			if (*str == '&' || (*str == '|' && *(str + 1) == '|'))
				str++;
			break ;
		}
		str++;
	}
	return (str + 1);
}
