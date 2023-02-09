/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 18:18:26 by okhiar            #+#    #+#             */
/*   Updated: 2023/01/31 20:05:07 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_execvp.h"

static int	count_words(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
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

static int	ft_strlen(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static char	*ft_make_str(char *str, char c)
{
	char	*word;
	int		len;
	int		i;

	i = -1;
	len = ft_strlen(str, c);
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (0);
	while (++i < len)
		word[i] = str[i];
	word[i] = 0;
	return (word);
}

static char	**free_all(char **strs, int i)
{
	while (--i >= 0)
	{
		free(strs[i]);
		strs[i] = 0;
	}
	free(strs);
	strs = NULL;
	return (NULL);
}

char	**ft_split(char *str, char c)
{
	char	**strs;
	int		count;
	int		i;

	i = 0;
	count = count_words(str, c);
	strs = (char **)malloc(sizeof(char *) * (count + 1));
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
