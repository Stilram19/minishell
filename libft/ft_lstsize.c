/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 09:18:08 by obednaou          #+#    #+#             */
/*   Updated: 2022/10/14 17:59:57 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	nodes_count;

	nodes_count = 0;
	while (lst)
	{
		nodes_count++;
		lst = lst->next;
	}
	return (nodes_count);
}
