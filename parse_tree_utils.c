/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 20:50:55 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/26 21:46:23 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*left_str(char *str, char *op)
{
	int		i;
	int		op_len;
	int		quote;
	int		parenth;
	char	*ret;

	i = 0;
	quote = 0;
	parenth = 0;
	op_len = ft_strlen(op);
	while (*(str + i))
	{
		open_close_quotes(*(str + i), &quote);
		(!quote && open_close_parenth(*(str + i), &parenth));
		if (!(quote || parenth || ft_strncmp(str + i, op, op_len)))
			break ;
		i++;
	}
	str = ft_substr(str, 0, i);
	ret = ft_strtrim(str, " "); 
	ft_garbage_collector(SINGLE_RELEASE, 0, str);
	return (ret);
}

char	*right_str(char *str, char *op)
{
	int		op_len;
	int		quote;
	int		parenth;
	char	*temp;
	char	*ret;

	quote = 0;
	parenth = 0;
	op_len = ft_strlen(op);
	while (*str)
	{
		open_close_quotes(*str, &quote);
		(!quote && open_close_parenth(*str, &parenth));
		if (!(quote || parenth || ft_strncmp(str, op, op_len)))
			break ;
		str++;
	}
	temp = ft_strdup(str + op_len);
	ret = ft_strtrim(temp, " ");
	ft_garbage_collector(SINGLE_RELEASE, 0, temp);
	ft_garbage_collector(SINGLE_RELEASE, 0, str);
	return (ret);
}
