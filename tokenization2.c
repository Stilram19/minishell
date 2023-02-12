/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:44:11 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/12 13:17:38 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special_char(char c, char *special_char, char *ignore)
{
	int	ret;

	ret = 0;
	if (c == '\'' || c == '\"')
	{
		if (*ignore == c)
			*ignore = 0;
		else if (!(*ignore))
			*ignore = c;
		return (0);
	}
	while (!(*ignore) && *special_char)
	{
		if (c == *special_char)
			ret = 1;
		special_char++;
	}
	return (ret);
}

int	is_escape_seq(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

char	*mask_generation(char *line)
{
	int		i;
	char	ignore;
	char	*mask;
	char	*special_char;

	i = 0;
	ignore = 0;
	special_char = "|<>&";
	mask = garbage_collector(ALLOCATE, ft_strlen(line) + 1, NULL);
	while (*(line + i))
	{
		if (!ignore && is_escape_seq(*(line + i)))
			*(mask + i) = '1';
		else if (is_special_char(*(line + i), special_char, &ignore))
			*(mask + i) = '2';
		else
			*(mask + i) = '0';
		i++;
	}
	*(mask + i) = '\0';
	return (mask);
}
