/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   production_rules1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:22:12 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/20 11:03:43 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fourth_production_rule(char *str)
{
	if ((*str == '&' && *(str + 1) == '&')
		|| *str == '|')
		return (1);
	return (0);
}

int	third_production_rule(char *str)
{
	int	c;
	int	ret;

	ret = 0;
	c = 0;
	while (*str)
	{
		(!ret && !is_blank(*str) && (ret = 1));
		open_close_quotes(*str, &c);
		if (!c && (*str == '&' || *str == '|'
				|| *str == '(' || *str == ')'))
			return (0);
		str++;
	}
	return (ret);
}

int	second_production_rule(char *str)
{
	int		ret;
	char	*new_str;

	ret = 0;
	if (third_production_rule(str))
		return (check_command_syntax(str));
	if (is_between_parenth(str))
	{
		remove_outer_parenth(&str);
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
