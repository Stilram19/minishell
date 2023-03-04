/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_without_garbage_collection.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:18:05 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/04 14:14:23 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strdup1(const char *s1)
{
	size_t	i;
	char	*copy;

	i = ft_strlen(s1);
	copy = malloc(sizeof(char) * (i + 1));
	if (!copy)
		return (0);
	*(copy + i) = 0;
	while (i--)
		*(copy + i) = *(s1 + i);
	return (copy);
}

char	*ft_strjoin1(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*join;

	if (!(s1 && s2))
		return (0);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	join = malloc(sizeof(char) * (i + j + 1));
	if (!join)
		return (0);
	ft_strlcpy(join, s1, i + 1);
	ft_strlcpy(join + i, s2, j + 1);
	return (join);
}
