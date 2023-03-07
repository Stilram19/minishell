/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 14:19:26 by okhiar            #+#    #+#             */
/*   Updated: 2023/03/07 22:11:08 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	_ft_putstr_fd(char *str, int fd, int ext)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	exit(ext);
}

char	*search_replace(char *str, char needle, char replacement)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == needle)
			str[i] = replacement;
		i++;
	}
	return (str);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

void	error_msg(char *msg)
{
	ft_putstr_fd(RED_BOLD, 2);
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(RESET, 2);
	ft_putstr_fd(msg, 2);
}
