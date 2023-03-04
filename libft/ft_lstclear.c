/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 10:06:31 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/04 16:57:46 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*head;
	t_list	*next_temp;

	if (!(lst && del))
		return ;
	head = *lst;
	while (head)
	{
		next_temp = head->next;
		ft_lstdelone(head, del);
		head = next_temp;
	}
	*lst = 0;
}
