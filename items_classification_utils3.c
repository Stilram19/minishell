/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items_classification_utils3.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:52:19 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/19 18:41:37 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

< file

int	is_redirect(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

char	*get_command(char **tokens)
{
	int	i;

	i = 0;
	while (*(tokens + i))
	{
		if (!is_redirect(**(tokens + i))
			&& (!i || !is_redirect(**(tokens + i - 1))))
			return (remove_quotes(*(tokens + i)));
		i++;
	}
	return (NULL);
}

char	**from_queue_to_array(t_queue *args)
{

}

char	**get_args(char **tokens, t_queue *args)
{
	int	i;

	i = 0;
	while (*(tokens + i))
	{
		if (!is_redirect(**(tokens + i))
			&& i && !is_redirect(**(tokens + i - 1)))
			
	}
}
