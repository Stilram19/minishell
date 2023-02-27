/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:08:07 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/27 17:52:39 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_all_blank(char *file_name)
{
	int	ret;

	ret = 1;
	while (*file_name)
	{
		if (!is_blank(*file_name) && ret--)
			break ;
		file_name++;
	}
	return (ret);
}

int	is_ambiguous_redirect(char **ptr_to_file_name)
{
	int		i;
	int		quotes;
	int		blank;
	char	*file_name;

	i = 0;
	quotes = 0;
	blank = 0;
	expand_if(ptr_to_file_name);
	file_name = *ptr_to_file_name;
	if (is_all_blank(file_name))
		return (1);
	while (*(file_name + i))
	{
		open_close_quotes(*(file_name + i), &quotes);
		if (!quotes && is_blank(*(file_name + i)) && ++blank)
			break ;
		i++;
	}
	while (blank && is_blank(*(file_name + i)))
		i++;
	return (*(file_name + i));
}
