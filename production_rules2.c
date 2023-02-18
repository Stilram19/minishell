/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   production_rules2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:25:24 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/18 14:48:47 by obednaou         ###   ########.fr       */
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

void	remove_outer_parenth(char **ptr_to_str)
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
