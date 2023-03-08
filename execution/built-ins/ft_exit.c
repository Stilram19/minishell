/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:25:27 by okhiar            #+#    #+#             */
/*   Updated: 2023/03/08 22:51:54 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_whitespace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	all_digits(char	*str)
{
	int		i;
	char	*nbr;

	i = 0;
	if (!str[0])
		return (0);
	nbr = ft_strtrim(str, " ");
	if (!nbr[0])
		return (0);
	if (nbr[0] == '-' || nbr[0] == '+')
		i++;
	while (nbr[i])
	{
		if (!ft_isdigit(nbr[i]))
			return (0);
		i++;
	}
	return (1);
}

void	exit_with_status(char *str)
{
	int	status;

	if (!str)
		status = 0;
	else if (all_digits(str))
		status = ft_atoi(str);
	else
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		status = 255;
	}
	exit(status);
}

int	ft_exit(char **args, int flag)
{
	if (flag)
		ft_putstr_fd("minishel: exit\n", 2);
	if (args[0] && args[1])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (EXIT_FAILURE);
	}
	exit_with_status(args[0]);
	return (EXIT_SUCCESS);
}
