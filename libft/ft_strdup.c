/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:40:03 by okhiar            #+#    #+#             */
/*   Updated: 2022/10/07 14:40:17 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*dup;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(str) + 1;
	dup = (char *)malloc(sizeof(char) * len);
	if (!dup)
		return (0);
	while (*str)
		dup[i++] = *str++;
	dup[i] = '\0';
	return (dup);
}
