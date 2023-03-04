/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:44:11 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/04 14:14:23 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
