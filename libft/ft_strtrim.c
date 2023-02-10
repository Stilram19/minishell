/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 08:47:48 by okhiar            #+#    #+#             */
/*   Updated: 2022/10/08 08:47:59 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_instr(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
		if (str[i++] == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	size_t	len;
	size_t	start;

	start = 0;
	if (!s1 || !set)
		return (0);
	while (ft_instr(set, *(s1 + start)) && *(s1 + start) != '\0')
		start++;
	len = ft_strlen(s1 + start);
	while (ft_instr(set, *(s1 + start + len - 1)) && len > 0)
		len--;
	trim = ft_substr(s1, start, len);
	return (trim);
}
