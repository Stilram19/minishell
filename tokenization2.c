/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:44:11 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/06 17:59:39 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	assign_mask1(char *mask, char *meta, int parenth, char c)
{
	if (parenth || c == ')')
		*mask = '6';
	else if (is_blank(c))
		*mask = '1';
	else if (ft_strchr(meta, c))
		*mask = (char)(ft_strchr(meta, c) - meta) + '2';
	else
		*mask = '0';
}

void	assign_mask2(char *mask, char *meta, char c)
{
	if (is_blank(c))
		*mask = '1';
	else if (ft_strchr(meta, c))
		*mask = '2' + (char)(ft_strchr(meta, c) - meta);
	else
		*mask = '0';
}

char	*mask_generation3(char *str, char *meta)
{
	int		i;
	int		quotes;
	int		parenth;
	char	*mask;

	i = 0;
	quotes = 0;
	parenth = 0;
	mask = ft_garbage_collector(ALLOCATE,
		sizeof(char) * (ft_strlen(str) + 1), NULL);
	while (*(str + i))
	{
		open_close_quotes(*(str + i), &quotes);
		if (!quotes || parenth)
		{
			open_close_parenth(*(str + i), &parenth);
			assign_mask1(mask + i, meta, parenth, *(str + i));
		}
		else
			*(mask + i) = '0';
		i++;
	}
	*(mask + i) = '\0';
	return (mask);
}

char	*mask_generation4(char *str, char *meta)
{
	int		i;
	int		quotes;
	char	*mask;

	i = 0;
	quotes = 0;
	mask = ft_garbage_collector(ALLOCATE,
		sizeof(char) * (ft_strlen(str) + 1), NULL);
	while (*(str + i))
	{
		open_close_quotes(*(str + i), &quotes);
		if (!quotes)
			assign_mask2(mask + i, meta, *(str + i));
		else
			*(mask + i) = '0';
		i++;
	}
	*(mask + i) = '\0';
	return (mask);
}
