/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:34:17 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/07 18:22:26 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free(char **tokens)
{
	int	i;

	i = 0;
	while (*(tokens + i))
	{
		ft_garbage_collector(SINGLE_RELEASE, 0, *(tokens + i));
		i++;
	}
	ft_garbage_collector(SINGLE_RELEASE, 0, tokens);
}

int	global_len(char **tokens)
{
	int	len;

	len = 0;
	while (*tokens)
	{
		len += ft_strlen(*tokens) + 1;
		tokens++;
	}
	return (len);
}

char	*join_tokens(char **tokens)
{
	int		i;
	int		j;
	int		len;
	char	*ret;

	i = 0;
	j = 0;
	len = global_len(tokens);
	ret = ft_garbage_collector(ALLOCATE, len + 1, NULL);
	while (*(tokens + i))
	{
		len = ft_strlen(*(tokens + i));
		ft_strlcpy(ret + j, *(tokens + i), len + 1);
		ft_strlcpy(ret + j + len, " ", 2);
		j += len + 1;
		i++;
	}
	*(ret + j) = '\0';
	ft_free(tokens);
	return (ret);
}

char	*get_prompt(int exit_status)
{
	if (exit_status)
		return (RED"➜ "RESET"minishell$ ");
	return (GRN"➜ "RESET"minishell$ ");
}
