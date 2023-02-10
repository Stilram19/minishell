/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 14:06:34 by okhiar            #+#    #+#             */
/*   Updated: 2022/10/25 15:19:19 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	words_count(char const *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count);
}

static int	ft_seplen(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
	i++;
	return (i);
}

static char	*ft_make_str(char const *str, char c)
{
	char	*word;
	int		i;
	int		len;

	i = 0;
	len = ft_seplen(str, c);
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (0);
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	**free_all(char **strs, size_t i)
{
	i--;
	while (i > 0)
	{
		free(strs[i]);
		strs[i] = 0;
		i--;
	}
	free(strs);
	strs = 0;
	return (0);
}

char	**ft_split(char const *str, char c)
{
	char	**strs;
	size_t	i;

	i = 0;
	strs = (char **)malloc(sizeof(char *) * (words_count(str, c) + 1));
	if (!strs)
		return (0);
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str)
		{
			strs[i] = ft_make_str(str, c);
			if (!strs[i])
				return (free_all(strs, i));
			i++;
		}
		while (*str && *str != c)
			str++;
	}
	strs[i] = 0;
	return (strs);
}
