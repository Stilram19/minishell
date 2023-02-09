/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvp_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 18:38:58 by okhiar            #+#    #+#             */
/*   Updated: 2023/01/31 20:26:06 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execvp.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *str)
{
	size_t		i;
	char		*new;

	i = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
		return (0);
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

void	*ft_memcpy(void *dest, void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*((char *) dest + i) = *((char *) src + i);
		i++;
	}
	return (dest);
}

char	*ft_strjoin(char *str1, char *str2)
{
	char	*ret;

	ret = (char *)malloc(sizeof(char) * \
				(ft_strlen(str1) + ft_strlen(str2) + 1));
	if (!ret)
		return (0);
	ft_memcpy(ret, str1, ft_strlen(str1));
	ft_memcpy(ret + ft_strlen(str1), str2, ft_strlen(str2) + 1);
	return (ret);
}
