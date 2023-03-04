/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 08:54:21 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/10 14:57:47 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*join;

	if (!(s1 && s2))
		return (0);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	join = ft_garbage_collector(ALLOCATE, (i + j + 1) * sizeof(char), NULL);
	if (!join)
		return (0);
	ft_strlcpy(join, s1, i + 1);
	ft_strlcpy(join + i, s2, j + 1);
	return (join);
}
