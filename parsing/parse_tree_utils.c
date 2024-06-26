/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 20:50:55 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/07 18:22:26 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_blank(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

char	*left_str(char *str, char *op)
{
	int		i;
	char	*ret;

	i = 0;
	while (*(str + i))
	{
		if (str + i == op)
			break ;
		i++;
	}
	str = ft_substr(str, 0, i);
	ret = ft_strtrim(str, " ");
	ft_garbage_collector(SINGLE_RELEASE, 0, str);
	return (ret);
}

char	*right_str(char *str, char *op, int with_op)
{
	int		op_len;
	char	*temp;
	char	*ret;

	op_len = ft_strlen(get_operator(op));
	if (with_op)
		temp = ft_strdup(op);
	else
		temp = ft_strdup(op + op_len);
	ret = ft_strtrim(temp, " ");
	ft_garbage_collector(SINGLE_RELEASE, 0, temp);
	ft_garbage_collector(SINGLE_RELEASE, 0, str);
	return (ret);
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
