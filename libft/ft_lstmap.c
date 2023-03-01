/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:06:24 by obednaou          #+#    #+#             */
/*   Updated: 2022/10/18 08:54:47 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_lst_temp;

	if (!(lst && f && del))
		return (0);
	new_lst_temp = ft_lstnew((*f)(lst->content));
	new_lst = new_lst_temp;
	lst = lst->next;
	while (lst && new_lst_temp)
	{
		new_lst_temp->next = ft_lstnew((*f)(lst->content));
		lst = lst->next;
		new_lst_temp = new_lst_temp->next;
	}
	if (!new_lst_temp)
		ft_lstclear(&new_lst, del);
	return (new_lst);
}
