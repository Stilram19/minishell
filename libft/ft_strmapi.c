/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 15:35:54 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/12 12:50:38 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*new_s;

	if (!(s && f))
		return (0);
	i = ft_strlen(s);
	new_s = ft_garbage_collector(ALLOCATE, (i + 1) * sizeof(char), NULL);
	if (!new_s)
		return (0);
	*(new_s + i) = 0;
	while (i--)
		*(new_s + i) = (*f)(i, *(s + i));
	return (new_s);
}
