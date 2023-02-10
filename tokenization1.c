/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:36:59 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/10 17:37:05 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*increment_count(char *mask, int *ptr_to_count)
{
	char	token_type;

	token_type = *mask;
	while (*mask == token_type)
		mask++;
	(*ptr_to_count)++;
	return (mask);
}

int	tokens_count(char *mask)
{
	int	count;

	count = 0;
	while (*mask)
	{
		if (*mask != '1')
			mask = increment_count(mask, &count) - 1;
		mask++;
	}
	return (count);
}

int	ft_token_len(char *mask)
{
	int		i;
	char	token_type;

	i = 0;
	token_type = *mask;
	while (*(mask + i) == token_type)
		i++;
	return (i);
}

char	*assign_token(char **ptr_to_line, char **ptr_to_mask)
{
	int		i;
	int		token_len;
	char	*token;

	i = 0;
	token_len = ft_token_len(*ptr_to_mask);
	//token = garbage_collector(ALLOCATE, (token_len + 1) * sizeof(char), NULL);
	token = malloc(sizeof(char) * (token_len + 1));
	while (i < token_len)
	{
		*(token + i) = *(*ptr_to_line + i);
		i++;
	}
	*(token + i) = '\0';
	(*ptr_to_line) += i;
	(*ptr_to_mask) += i;
	return (token);
}

char	**produce_tokens(char *line, char *mask)
{
	int		j;
	int		size;
	char	**tokens;

	j = 0;
	size = tokens_count(mask) + 1;
	//tokens = ft_garbage_collector(ALLOCATE, sizeof(char *) * size, NULL);
	tokens = malloc(sizeof(char *) * size);
	while (*line)
	{
		if (*mask != '1')
		{
			*(tokens + j) = assign_token(&line, &mask);
			j++;
			continue ;
		}
		line++;
		mask++;
	}
	*(tokens + j) = NULL;
	return (tokens);
}
