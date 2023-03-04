/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvp_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 14:03:21 by okhiar            #+#    #+#             */
/*   Updated: 2023/03/04 14:06:48 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

char	*_ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	tlen;

	tlen = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (tlen + 1));
	if (!str)
		return (0);
	ft_memcpy(str, s1, ft_strlen(s1));
	ft_memcpy((str + ft_strlen(s1)), s2, ft_strlen(s2) + 1);
	return (str);
}

char	*_ft_strdup(const char *str)
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