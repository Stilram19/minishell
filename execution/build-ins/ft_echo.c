/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:18:17 by okhiar            #+#    #+#             */
/*   Updated: 2023/02/12 17:21:45 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

int	check_option(char *option, int *start)
{
	int	i;

	i = 0;
	if (!ft_strncmp(option, "-n", 2))
	{
		i += 2;
		while (option[i] && option[i] == 'n')
			i++;
		if (!option[i])
		{
			(*start)++;
			return (1);
		}
	}
	return (0);
}

int	ft_echo(char **args)
{
	int	i;
	int	flag;

	i = 0;
	flag = check_option(args[0], &i);
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
