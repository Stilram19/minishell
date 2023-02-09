/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:01:55 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/09 18:10:23 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief allocates a new node of type t_list
 * writes the value of the pointer data in the data field
 * of the new node.
*/
t_list	*ft_lstnew(void *data)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->data = data;
	new->next = 0;
	return (new);
}

/**
 @brief allocates heap memory for a new t_list node, and adds it
 in the front of the head of the list.
 @param ptr_to_head{t_list **} pointer to the head pointer of the
 linked list.
 @param data{void *} pointer which contains a freeable heap address.
*/
t_list	*ft_lstadd_front(t_list **ptr_to_head, void *data)
{
	t_list	*new;

	new = ft_lstnew(data);
	if (!new)
		return (NULL);
	new->next = *ptr_to_head;
	*ptr_to_head = new;
	return (new);
}

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
