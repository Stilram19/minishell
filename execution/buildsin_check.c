/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildsin_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:04:16 by okhiar            #+#    #+#             */
/*   Updated: 2023/03/04 13:35:25 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	in_array(char **arr, char *key)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (ft_strcmp(arr[i], key) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	is_buildin(char *cmd)
{
	static char	*buildin[8] = {"cd", "echo", "pwd", "export", \
								"unset", "exit", "env", NULL};

	if (in_array(buildin, cmd))
		return (1);
	return (0);
}
