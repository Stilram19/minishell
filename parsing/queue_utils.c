/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 16:31:29 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/07 18:22:26 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	queue_init(t_queue *q)
{
	q->first = NULL;
	q->last = NULL;
	q->len = 0;
}

void	queue_push(t_queue *q, void *data)
{
	t_item	*new;

	new = ft_garbage_collector(ALLOCATE, sizeof(t_node), NULL);
	new->data = data;
	new->next = NULL;
	q->len++;
	if (q->first)
	{
		q->last->next = new;
		q->last = new;
		return ;
	}
	q->first = new;
	q->last = new;
}

void	*queue_pop(t_queue *q)
{
	void	*ret;
	t_item	*temp;

	ret = NULL;
	if (q->first)
	{
		q->len--;
		temp = q->first;
		ret = temp->data;
		q->first = q->first->next;
		ft_garbage_collector(SINGLE_RELEASE, 0, temp);
	}
	return (ret);
}

void	*queue_first(t_queue *q)
{
	void	*data;

	data = NULL;
	if (q->first)
		data = q->first->data;
	return (data);
}
