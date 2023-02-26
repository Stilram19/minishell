/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 20:18:45 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/26 21:52:25 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_close_quotes(char c, int *ptr_to_flag)
{
	int	flag;

	flag = *ptr_to_flag;
	if (c == '\'' || c == '\"')
	{
		if (c == flag)
			flag = 0;
		else if (!flag)
			flag = c;
	}
	*ptr_to_flag = flag;
}

void	open_close_parenth(char c, int *ptr_to_flag)
{
	int	flag;

	flag = *ptr_to_flag;
	if (c == '(')
		flag++;
	if (c == ')')
		flag--;
	*ptr_to_flag = flag;
}

char	*remove_outer_parenth(char *str)
{
	int		len;
	char	*new_str;

	len = ft_strlen(str);
	*(str + len - 1) = '\0';
	new_str = ft_strdup(str + 1);
	ft_garbage_collector(SINGLE_RELEASE, 0, str);
	return (new_str);
}
