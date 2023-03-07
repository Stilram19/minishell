/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 10:37:00 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/07 18:22:26 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief releases the given address in the collection.
*/
void	single_release(t_list **ptr_to_head, void *to_free)
{
	t_list	*temp1;
	t_list	*temp2;

	temp1 = *ptr_to_head;
	if (!temp1)
		return ;
	if ((*ptr_to_head)->content == to_free)
	{
		temp1 = (*ptr_to_head)->next;
		ft_lstdelone(*ptr_to_head, free);
		*ptr_to_head = temp1;
		return ;
	}
	while (temp1->next)
	{
		if (temp1->next->content == to_free)
		{
			temp2 = temp1->next->next;
			ft_lstdelone(temp1->next, free);
			temp1->next = temp2;
			return ;
		}
		temp1 = temp1->next;
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

	ptr = NULL;
	if (option == ALLOCATE)
	{
		ptr = malloc(size);
		if (!ptr)
			exit(EXIT_FAILURE);
		ft_lstadd_front(&head, ft_lstnew(ptr));
		return (ptr);
	}
	if (option == SINGLE_RELEASE)
	{
		if (to_free)
			single_release(&head, to_free);
		return (to_free);
	}
	ft_lstclear(&head, free);
	return (ptr);
}
