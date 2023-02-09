/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:01:55 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/09 18:47:42 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief releases every allocated block of memory refered to by the collection
 * of pointers (data field in t_list), even memory allocated for the nodes
 * of the linked list whose head is the argument head.
*/
void	release_heap(t_list *head)
{
	t_list	*next;

	while (head)
	{
		next = head->next;
		free(head->data);
		free(head);
		head = next;
	}
}

/**
 * @brief collects pointers refering to allocated memory in the heap,
 * and releases the blocks of memory refered to by the collection of pointers
 * , collected so far.
 * @param ptr{void *} collects the value of the pointer in case of a set pointer,
 * and releases every block of memory refered to by a pointer in the collection
 * if the pointer is NULL.
 * @return {int} 0 in case of success
*/
int	ft_heap_management(void *ptr)
{
	static t_list	*head;

	if (!ptr)
	{
		release_heap(head);
		return (SUCCESS);
	}
	if (ft_lstadd_front(&head, ft_lstnew(ptr)))
		return (SUCCESS);
	return (ERROR);
}
