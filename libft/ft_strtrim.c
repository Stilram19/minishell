/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 09:25:49 by obednaou          #+#    #+#             */
/*   Updated: 2022/10/19 19:30:44 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_it_in_set(char const *set, char c)
{
	size_t	i;

	i = 0;
	while (*(set + i))
	{
		if (*(set + i) == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	ft_first_proper_char(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (*(s1 + i) && ft_is_it_in_set(set, *(s1 + i)))
		i++;
	return (i);
}

static size_t	ft_last_proper_char(char const *s1, char const *set)
{
	size_t	i;

	if (!ft_strlen(s1))
		return (0);
	i = ft_strlen(s1) - 1;
	while ((i > 0) && ft_is_it_in_set(set, *(s1 + i)))
			i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*ret;

	if (!s1)
		return (0);
	if (!set)
		return ((char *)ft_strdup(s1));
	i = -1;
	start = ft_first_proper_char(s1, set);
	end = ft_last_proper_char(s1, set);
	if (start <= end && *s1)
		ret = malloc((end - start + 2) * sizeof(char));
	else
		ret = malloc(sizeof(char));
	if (!ret)
		return (0);
	while (++i + start <= end)
		*(ret + i) = *(s1 + start + i);
	if (*ret)
		*(ret + i) = 0;
	return (ret);
}
