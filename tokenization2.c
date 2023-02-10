/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:44:11 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/10 17:44:37 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special_char(char c, char *special_char, int *inside_quote)
{
	int	ret;

	ret = 0;
	while (*special_char)
	{
		if (c == *special_char)
			ret = 1;
		special_char++;
	}
	if (ret == 1 && *special_char == '\'')
		inside_quote = !(inside_quote);
	return (ret);
}

int	is_escape_seq(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
}

char	*mask_generation(char *line)
{
	char	*mask;
	char	*special_char;
	int		inside_quote;

	//mask = garbage_collector(ALLOCATE, ft_strlen(line) + 1, NULL);
	inside_quote = 0;
	special_char = "[\'\"|<>&]";
	mask = malloc(sizeof(char) * (ft_strlen(line) + 1));
	while (*line)
	{
		if (!inside_quote && is_escape_seq(*line))
			*mask = '1';
		else if (is_special_char(*line, special_char, &inside_quote))
			*mask = '2';
		else
			*mask = '0';
		line++;
		mask++;
	}
	return (mask);
}
