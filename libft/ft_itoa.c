/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 14:14:34 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/12 12:50:16 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_digits_count(int n)
{
	int	count;

	count = 0;
	if (!n)
		return (1);
	if (n < 0)
	{
		if (n == -2147483648)
			return (11);
		n *= -1;
		count++;
	}
	while (n > 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*ret;
	int		i;

	i = ft_digits_count(n);
	ret = ft_garbage_collector(ALLOCATE, (i + 1) * sizeof(char), NULL);
	if (!ret)
		return (0);
	if (n < 0)
		*ret = 45;
	if (!n)
		*ret = 48;
	*(ret + i) = 0;
	while (n)
	{
		i--;
		if (n < 0)
			*(ret + i) = -(n % 10) + 48;
		else
			*(ret + i) = n % 10 + 48;
		n /= 10;
	}
	return (ret);
}
