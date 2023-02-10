/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:52:12 by okhiar            #+#    #+#             */
/*   Updated: 2022/10/19 21:40:16 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	nlen;
	int		check;

	if (!(*needle))
		return ((char *)haystack);
	if (!haystack && !len)
		return (0);
	nlen = ft_strlen(needle);
	while (*haystack && len >= nlen)
	{
		check = ft_strncmp(haystack, needle, nlen);
		if (!check)
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (0);
}

//len -= (nlen - 1);