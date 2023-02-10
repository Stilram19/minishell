/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 21:35:22 by okhiar            #+#    #+#             */
/*   Updated: 2022/10/06 21:35:35 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	int				result;
	unsigned long	tmp;

	i = 0;
	sign = 1;
	result = 0;
	tmp = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		sign = 1 - 2 * (str[i++] == '-');
	while (ft_isdigit(str[i]))
	{
		tmp *= 10;
		tmp += str[i] - 48;
		if (tmp > __LONG_MAX__ + (sign < 0))
			return (-1 + (sign < 0));
		result = tmp;
		i++;
	}
	return (result * sign);
}
