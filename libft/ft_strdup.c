/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 17:58:33 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/10 10:29:16 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*copy;

	i = ft_strlen(s1);
	copy = ft_garbage_collector(ALLOCATE, (i + 1) * sizeof(char));
	if (!copy)
		return (0);
	*(copy + i) = 0;
	while (i--)
		*(copy + i) = *(s1 + i);
	return (copy);
}
