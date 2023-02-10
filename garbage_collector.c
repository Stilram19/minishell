/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 10:37:00 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/10 11:48:27 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief releases the mentioned address in the collection.
*/
void	single_release(t_list **ptr_to_head, void *to_free)
{
	t_list	*temp;
	t_list	*temp1;

	temp = *ptr_to_head;
	if (*ptr_to_head && (*ptr_to_head)->content == to_free)
	{
		temp = (*ptr_to_head)->next;
		ft_lstdelone(*ptr_to_head, free);
		*ptr_to_head = temp;
		return ;
	}
	while (temp->next)
	{
		if (temp->next->content == to_free)
		{
			temp1 = temp->next->next;
			ft_lstdelone(temp->next, free);
			temp->next = temp1;
			return ;
		}
		temp = temp->next;
	}
}

/**
 * @brief very simple, but useful implementation of 
 * a garbage collector, especially for memory leaks.
 * Allocate, collects and releases all allocated memory
 * when needed.
 * @param option{int} specifies whether the caller asks to
 * allocate memory, or asks to release all allocated memory
 * so far.
 * @param size{int} the number of bytes the caller wish to allocate
 * @return the address of the first byte of the allocated block, 
 * NULL otherwise.
*/
void	*ft_garbage_collector(int option, int size, void *to_free)
{
	void			*ptr;
	static t_list	*head;

	if (option == ALLOCATE)
	{
		ptr = malloc(size);
		ft_lstadd_front(&head, ft_lstnew(ptr));
		return (ptr);
	}
	if (option == SINGLE_RELEASE)
	{
		single_release(&head, to_free);
		return (NULL);
	}
	ft_lstclear(&head, free);
	return (NULL);
}
