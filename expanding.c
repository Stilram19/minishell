/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 18:21:19 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/14 12:03:52 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	var_name_len(char *var)
{
	int	i;

	i = 0;
	while (ft_isalnum(*(var + i)) || *(var + i) == '_')
		i++;
	if (!i && *var == '?')
		i++;
	return (i);
}

char	*var_expansion(char **ptr_to_token, int *ptr_to_i, int name_len)
{
	int		new_len;
	int		value_len;
	char	*var_value;
	char	*var_name;
	char	*to_free;

	value_len = 0;
	var_name = ft_strdup(*ptr_to_token + *ptr_to_i);
	*(var_name + name_len) = '\0';
	var_value = get_var_value(var_name);
	if (var_value)
		value_len = ft_strlen(var_value);
	to_free = *ptr_to_token;
	new_len = ft_strlen(to_free) + value_len - (name_len + 1);
	*ptr_to_token = ft_garbage_collector(ALLOCATE, new_len + 1, NULL);
	ft_strlcpy(*ptr_to_token, to_free, *ptr_to_i);
	if (var_value)
		ft_strlcpy(*ptr_to_token + *ptr_to_i - 1, var_value, value_len + 1);
	ft_strlcpy(*ptr_to_token + *ptr_to_i - 1 + value_len, to_free
		+ *ptr_to_i + name_len, new_len - value_len - *ptr_to_i + 2);
	ft_garbage_collector(SINGLE_RELEASE, 0, to_free);
	ft_garbage_collector(SINGLE_RELEASE, 0, var_name);
	*ptr_to_i += value_len - 1;
	return (*ptr_to_token);
}

// void	expand_if(char **tokens)
// {
// 	int		i;
// 	char	open_quote;
// 	char	*token;

// 	i = 0;
// 	open_quote = 0;
// 	token = *tokens;
// 	while (*(token + i))
// 	{
// 		if (*(token + i) == '\'' || *(token + i) == '\"')
// 		{
// 			if (*(token + i) == open_quote)
// 				open_quote = 0;
// 			else if (*(token + i) == open_quote)
// 				open_quote = *(token + i);
// 		}
// 		while (!open_quote && *(token + i) && *(token + i) != '$')
// 			i++;
// 		if (!(*(token + i)))
// 			break ;
// 		if ((++i && *(token + i) != '?'
// 				&& !ft_isalnum(*(token + i))) || open_quote)
// 			continue ;
// 		token = var_expand(tokens, &i, var_name_len(token + i));
// 	}
// }

// $' or $" -> $ should be removed from the string
// but there must be no open quote before $ 

int	remove_dollar_if(char *add, int open_quote)
{
	if (!(*add) || (*add != '\'' && *add != '\"')
		|| open_quote)
		return (0);
	while (*(add - 1))
	{
		*(add - 1) = *add;
		add++;
	}
	return (1);
}

void	expand_if(char **tokens)
{
	int		i;
	char	open_quote;
	char	*token;

	i = 0;
	open_quote = 0;
	token = *tokens;
	while (*(token + i))
	{
		if (*(token + i) == '\'' || *(token + i) == '\"')
		{
			if (open_quote == *(token + i++))
				open_quote = 0;
			else if (!open_quote)
				open_quote = *(token + i - 1);
			continue ;
		}
		if (((*(token + i) != '$' || open_quote == '\'') && ++i)
			|| remove_dollar_if(token + i + 1, open_quote))
			continue ;
		if (++i && !ft_isalnum(*(token + i)) && *(token + i) != '?')
			continue ;
		token = var_expansion(tokens, &i, var_name_len(token + i));
	}
}

void	expanding(char **tokens)
{
	int		ambig_redir;
	char	*token;
	char	**tokens_temp;

	ambig_redir = 0; 
	tokens_temp = tokens;
	while (*tokens_temp)
	{
		if (ft_strchr(*tokens_temp, '$'))
			expand_if(tokens_temp);
		tokens_temp++;
	}
	while (*tokens)
	{
		token = *tokens;
		if (ft_strncmp(token, ">", 1)
			&& ft_strncmp(token, "<", 1) && ++tokens)
			continue ;
		token = *(++tokens);
		if (!token || !(*token))
			ambig_redir = 1;
	}
	if (ambig_redir)
		printf("ambiguous redirect\n");
}
