/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items_classification_utils3.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:52:19 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/22 14:05:50 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_command(char **tokens)
{
	int	i;

	i = 0;
	while (*(tokens + i))
	{
		if (!is_redirect(*(tokens + i))
			&& (!i || !is_redirect(*(tokens + i - 1))))
			return (remove_quotes(*(tokens + i)));
		i++;
	}
	return (NULL);
}

void	**from_queue_to_array(t_queue *q)
{
	int		i;
	int		len;
	void	**array;

	i = -1;
	len = q->len;
	array = ft_garbage_collector(ALLOCATE,
		sizeof(void *) * (len + 1), NULL);
	while (++i < len)
		*(array + i) = queue_pop(q);
	*(array + i) = NULL;
	return (array);
}

void	encode_non_wildcard(char *arg)
{
	int	encode_enable;

	encode_enable = 0;
	while (*arg)
	{
		if (*arg == '\'' || *arg == '\"')
		{
			if (*arg == encode_enable)
				encode_enable = 0;
			else if (!encode_enable)
				encode_enable = *arg;
		}
		if (encode_enable && *arg == '*')
			*arg = -1;
		arg++;
	}
}

char	**get_args(char **tokens, t_queue *args)
{
	int		i;
	char	*arg;

	i = 0;
	while (*(tokens + i))
	{
		if (!is_redirect(*(tokens + i))
			&& i && !is_redirect(*(tokens + i - 1)))
		{
			arg = *(tokens + i);
			if (ft_strchr(arg, '*'))
				encode_non_wildcard(arg);
			queue_push(args, remove_quotes(arg));
		}
		i++;
	}
	return ((char **)from_queue_to_array(args));
}
