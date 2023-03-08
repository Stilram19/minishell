/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:53:02 by okhiar            #+#    #+#             */
/*   Updated: 2023/03/08 23:31:17 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*set_mask(char *name, int len)
{
	char	*mask;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	mask = ft_garbage_collector(ALLOCATE, sizeof(char) * (len + 1), NULL);
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			flag = 1;
		mask[i] = ((ft_isalnum(name[i]) || name[i] == '_') * 48) + \
					(flag * 49 + (name[i] == '+'));
		flag = 0;
		i++;
	}
	mask[i] = '\0';
	return (mask);
}

int	is_exist(char **env, char *identifier)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(identifier);
	while (env[i])
	{
		if (!ft_strncmp(identifier, env[i], len) \
			&& (!env[i][len] || env[i][len] == '='))
			return (i);
		i++;
	}
	return (-1);
}

int	name_len(char *name, int *append)
{
	int	i;

	i = 0;
	while (name[i])
	{
		if (append && name[i] == '=')
			break ;
		i++;
	}
	return (i);
}

int	valid_arg(char *arg, int *append)
{
	int		i;
	int		len;
	char	*mask;
	char	*name;

	i = 0;
	len = name_len(arg, append);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	name = ft_substr(arg, 0, len);
	mask = set_mask(name, len);
	while (mask[i])
	{
		if (mask[i] == 49 || (!append && mask[i] != 48) || (mask[0] != 48) \
			|| (append && mask[i] == 50 && arg[i + 1] != '='))
			return (0);
		i++;
	}
	if (append)
	{
		*append = 0;
		if (mask[i - 1] == 50)
			*append = 1;
	}
	return (1);
}
