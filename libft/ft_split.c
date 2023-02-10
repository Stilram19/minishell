/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 11:07:47 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/10 10:30:27 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_arrlen(char const *s, char c)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (*(s + i))
	{
		while (*(s + i) && *(s + i) == c)
			i++;
		if (*(s + i))
			size++;
		while (*(s + i) && *(s + i) != c)
			i++;
	}
	return (size);
}

static void	free_the_heap(void	*ptr, size_t j)
{
	while (j--)
		free((void *)ptr + j);
	free(ptr);
}

static char	*ft_allocate_word(char **arr, const char **s, char c, int j)
{
	size_t		i;
	char		*str;
	const char	*s1;

	i = 0;
	s1 = *s;
	while (*(s1 + i) && *(s1 + i) != c)
		i++;
	*s = s1 + i;
	str = ft_garbage_collector(ALLOCATE, (i + 1) * sizeof(char));
	if (!str)
	{
		free_the_heap(arr, j);
		return (0);
	}
	*(str + i) = 0;
	while (i > 0)
	{
		i--;
		*(str + i) = *(s1 + i);
	}
	return (str);
}

char	**ft_split(char const *s, char c)
{
	size_t	j;
	char	**arr;

	j = 0;
	if (!s)
		return (0);
	arr = ft_garbage_collector(ALLOCATE,
			(ft_arrlen(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (0);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			*(arr + j) = ft_allocate_word(arr, &s, c, j);
			if (!*(arr + j))
				return (0);
			j++;
		}
	}
	*(arr + j) = 0;
	return (arr);
}
