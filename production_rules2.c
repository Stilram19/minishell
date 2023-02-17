/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   production_rules2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:25:24 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/17 15:03:17 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_brackets(char c, t_balance *b)
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

void	remove_outer_brackets(char **ptr_to_str)
{
	char	*str;

	str = *ptr_to_str;
	while (is_blank(*str))
		str++;
	*ptr_to_str = str + 1;
	while (*str)
		str++;
	str--;
	while (is_blank(*str))
		str--;
	*str = '\0';
}

int	check_command_syntax(char *str)
{
	char	*mask;
	char	**tokens;

	mask = mask_generation(str);
	tokens = produce_tokens(str, mask);
	return (check_syntax(tokens));
}

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
