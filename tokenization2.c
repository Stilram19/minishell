/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:44:11 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/04 20:45:27 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_blank(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

char	*mask_generation(char *line)
{
	int		i;
	int		ignore;
	char	*mask;

	i = 0;
	ignore = 0;
	mask = ft_garbage_collector(ALLOCATE, ft_strlen(line) + 1, NULL);
	while (*(line + i))
	{
		open_close_quotes(*(line + i), &ignore);
		if (!ignore && is_blank(*(line + i)))
			*(mask + i) = '1';
		else if (!ignore && (*(line + i) == '<' || *(line + i) == '>'))
			*(mask + i) = '2';
		else
			*(mask + i) = '0';
		i++;
	}
	*(mask + i) = '\0';
	return (mask);
}

char	*mask_generation2(char *line)
{
	int		i;
	int		ignore;
	char	*mask;

	i = 0;
	ignore = 0;
	mask = ft_garbage_collector(ALLOCATE, ft_strlen(line) + 1, NULL);
	while (*(line + i))
	{
		open_close_quotes(*(line + i), &ignore);
		if (!ignore && is_blank(*(line + i)))
			*(mask + i) = '1';
		else
			*(mask + i) = '0';
		i++;
	}
	*(mask + i) = '\0';
	return (mask);
}

void	assign_mask_if(char *mask, char c, int parenth)
{
	if (parenth || c == ')')
	{
		*mask = '3';
		return ;
	}
	if (is_blank(c))
		*mask = '1';
	if (is_operator(c))
		*mask = '2';
	else
		*mask = '0';
}

char	*mask_generation3(char *str)
{
	int		quotes;
	int		parenth;
	char	*mask;

	quotes = 0;
	parenth = 0;
	mask = ft_garbage_collector(ALLOCATE,
		sizeof(char) * (ft_strlen(str) + 1), NULL);
	while (*str)
	{
		open_close_quotes(*str, &quotes);
		if (!quotes)
		{
			open_close_parenth(*str, &parenth);
			assign_mask_if(*str, parenth, mask);
		}
		else
			*mask = '0';
		str++;
		mask++;
	}
	*mask = '\0';
	return (mask);
}
