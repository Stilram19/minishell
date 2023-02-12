/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 18:21:19 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/12 18:36:54 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// first encountered character in the list {', ", $}
// if ' is the first encountered character, then no expanding happens.
// if " or $ is the first encountered character, then it may expand.
// skip every charcter before $
// go through characters after $, until you find a non-apha-numeric character{'\0', $, "} are included.
// if '\0' is directely after $, don't expand, let things as it is.
// otherwise look for the variable found between $ and the first encountered non-alpha-numeric character.
// Reallocate for this token, and keep every character before $, and here:
// if you find the variable then substitute it with its value.
// otherwise skip it (as if nothing existed before).

char first_encountered(char *token)
{
	char ret;

	ret = 0;
	while (*token)
	{
		if (*token == '\'' || *token == '\"' || *token == '$')
		{
			ret = *token;
			break ;
		}
		token++;
	}
	return (ret);
}

int	var_name_len(char *var)
{
	int	i;

	i = 0;
	while (ft_isalnum(*(var + i)))
		i++;
	if (!i && *var == '?')
		i++;
	return (i);
}

char	*var_expand(char **ptr_to_token, int *ptr_to_i, int name_len)
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
	//printf("%s\n", *(tokens + index));
	ft_strlcpy(*ptr_to_token + *ptr_to_i - 1 + value_len, to_free + *ptr_to_i + name_len,
		new_len - value_len - *ptr_to_i + 2);
	//printf("%s\n", *ptr_to_token);
	ft_garbage_collector(SINGLE_RELEASE, 0, to_free);
	ft_garbage_collector(SINGLE_RELEASE, 0, var_name);
	*ptr_to_i += value_len - 1;
	return (*ptr_to_token);
}
//<$HOME$HOME>
//</Users/obednaou$HOME
//i = 1
//name_len = 4
//var_name = <HOME>;
void expand_if(char **tokens, int index)
{
	int		i;
	char	*token;

	i = 0;
	token = *(tokens + index);
	if (first_encountered(token) == '\'')
		return ;
	while (*(token + i))
	{
		while (*(token + i) && *(token + i) != '$')
			i++;
		if (!(*(token + i)))
			break ;
		if (++i && *(token + i) != '?' && !ft_isalnum(*(token + i)))
			continue ;
		token = var_expand(tokens + index, &i, var_name_len(token + i));
	}
}

void expanding(char **tokens)
{
	int i;
	char **my_env;

	i = 0;
	my_env = get_env(NULL);
	while (*(tokens + i))
	{
		if (ft_strchr(*(tokens + i), '$'))
			expand_if(tokens, i);
		i++;
	}
}
