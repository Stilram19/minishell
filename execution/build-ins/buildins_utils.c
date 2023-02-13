/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:53:02 by okhiar            #+#    #+#             */
/*   Updated: 2023/02/13 12:44:34 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

static char	*set_mask(char *name, int len)
{
	char	*mask;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	mask = (char *)malloc(sizeof(char) * (len + 1));
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '=')
			flag = 1;
		mask[i] = ((ft_isalnum(name[i])) * 48) + \
					(flag * 49 + (name[i] == '+')) + ((name[i] == '=') * 51);
		flag = 0;
		i++;
	}
	mask[i] = '\0';
	return (mask);
}

int	name_len(char *name)
{
	int	i;

	i = 0;
	while (name[i] && name[i] != '=')
		i++;
	return (i);
}

int	valid_arg(char *arg, int *append)
{
	int		i;
	int		len;
	char	*mask;
	char	*name;

	len = name_len(arg);
	i = 0;
	if (arg[len] == '=')
		len++;
	name = ft_substr(arg, 0, len);
	mask = set_mask(name, len);
	while (mask[i])
	{
		if (mask[i] == 49 || (mask[i] == 50 && mask[i + 1] != 51) 
			|| (mask[0] != 48))
			return (0);
		i++;
	}
	*append = 0;
	if (mask[i - 2] == 50 && mask[i - 1] == 51)
		*append = 1;
	return (1);
}
