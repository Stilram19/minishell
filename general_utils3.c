/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:34:17 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/06 17:20:54 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (*(tokens + i))
	{
		i++;
		len += ft_strlen(*(tokens + i));
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
		j += len;
		ft_strlcpy(ret + j, *(tokens + i), len + 1);
		i++;
	}
	ft_free(tokens);
	return (ret);
}

char	*get_prompt(int exit_status)
{
	if (exit_status)
		return (RED"➜ "reset"minishell$ ");
	return (GRN"➜ "reset"minishell$ ");
}