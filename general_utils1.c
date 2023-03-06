/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 20:18:45 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/06 22:21:21 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_close_quotes(char c, int *ptr_to_flag)
{
	int	flag;

	flag = *ptr_to_flag;
	if (c == '\'' || c == '\"')
	{
		if (c == flag)
			flag = 0;
		else if (!flag)
			flag = c;
	}
	*ptr_to_flag = flag;
}

void	open_close_parenth(char c, int *ptr_to_flag)
{
	int	flag;

	flag = *ptr_to_flag;
	if (c == '(')
		flag++;
	if (c == ')')
		flag--;
	*ptr_to_flag = flag;
}

char	*remove_outer_parenth(char *str)
{
	int		len;
	char	*new_str;

	len = ft_strlen(str);
	*(str + len - 1) = '\0';
	new_str = ft_strdup(str + 1);
	ft_garbage_collector(SINGLE_RELEASE, 0, str);
	return (new_str);
}

char	*remove_outer_parenth2(char *str)
{
	int		len;
	char	*new_str;

	new_str = ft_strdup(str + 1);
	len = ft_strlen(new_str);
	*(new_str + len - 1) = '\0';
	return (new_str);
}

char	*unmask_quotes(char *str)
{
	int	i;

	i = 0;
	while (*(str + i))
	{
		if (*(str + i) == SINGLE_QUOTE_MASK)
			*(str + i) = '\'';
		else if (*(str + i) == DOUBLE_QUOTE_MASK)
			*(str + i) = '\"';
		i++;
	}
	return (str);
}

char	*random_file_name_generation(void)
{
	int		i;
	int		j;
	int		fd;
	char	buff[100];
	char	random_name[11];

	i = 0;
	fd = open("/dev/random", O_RDONLY);
	random_name[10] = '\0';
	buff[99] = '\0';
	while (i < 10)
	{
		j = 0;
		read(fd, buff, 99);
		while (*(buff + j) && i < 10)
		{
			if (ft_isalnum(*(buff + j)))
				*(random_name + i++) = *(buff + j);
			j++;
		}
	}
	close(fd);
	return (ft_strjoin("/tmp/", random_name));
}
