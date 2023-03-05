/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:34:17 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/05 18:35:11 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char **tokens)
{
	int	i;

	i = 0;
	while (*(tokens + i))
	{
		ft_garbage_collector(SINGLE_RELEASE, 0, *(tokens + i));
		i++;
	}
	ft_garbage_collector(SINGLE_RELEASE, 0, tokens);
}


