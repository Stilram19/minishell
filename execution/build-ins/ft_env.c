/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:43:52 by okhiar            #+#    #+#             */
/*   Updated: 2023/02/11 14:35:01 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"
#include "../../minishell.h"

int	ft_env(void)
{
	int		i;
	char	**env;

	env = get_env(NULL);
	i = 0;
	while (env[i])
		printf("%s\n", env[i++]);
}