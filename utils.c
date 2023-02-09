/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:30:09 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/09 18:38:42 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*build_env(char **env)
{
	int	i;

	i = 0;
	while (*(env + i))
	{
		
	}
}

t_list	*get_env(char **env)
{
	static t_list	*my_env;

	if (!my_env)
		my_env = build_env(env);
	return (my_env);
}
