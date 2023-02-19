/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items_classification_utils3.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:52:19 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/19 20:35:15 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirect(char *c)
{
	if (*c == '<' || *c == '>')
		return (1);
	return (0);
}

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

char	**from_queue_to_array(t_queue *q)
{
	int		i;
	char	**array;

	i = -1;
	array = malloc(sizeof(void *) * (q->len + 1));
	while (++i < q->len)
		*(array + i) = queue_pop(q);
	*(array + i) = NULL;
	return (array);
}

char	**get_args(char **tokens, t_queue *args)
{
	int		i;

	i = 0;
	while (*(tokens + i))
	{
		if (!is_redirect(*(tokens + i))
			&& i && !is_redirect(*(tokens + i - 1)))
			queue_push(args, remove_quotes(*(tokens + i)));
		i++;
	}
	return (from_queue_to_array(args));
}
