/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:43:52 by okhiar            #+#    #+#             */
/*   Updated: 2023/03/09 02:58:07 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(void)
{
	int		i;
	char	**env;

	env = get_env(NULL);
	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '=') && env[i][0] != '?')
			printf("%s\n", env[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
