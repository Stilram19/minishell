/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:18:17 by okhiar            #+#    #+#             */
/*   Updated: 2023/02/17 18:26:11 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

int	check_option(char *option)
{
	int	i;

	i = 2;
	while (option[i] && option[i] == 'n')
		i++;
	if (!option[i])
		return (1);
	return (0);
}

int	is_all_question_mark(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i] && str[i] == '?')
		i++;
	if (!str[i])
		return (1);
	return (0);
}

int	ft_echo(char **args)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (args[i] && !ft_strncmp(args[i], "-n", 2) && check_option(args[i]))
	{
		flag = 1;
		i++;
	}
	while (args[i])
	{
		// if (is_all_question_mark(args[i]))
		// 	print_files_dirs(ft_strlen(args[i]));
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
