/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:08:07 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/05 16:18:57 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// var="' '", >$var, >c$var --> ambiguous redirection
// var=" ", >""$var, >$var"" --> ambiguous redirection
// >""$empty, >$empty"" --> no such file or directory
// >$empty --> ambiguous redirection

int	is_all_blank(char *file_name)
{
	int	ret;
	int	quotes;

	ret = 0;
	quotes = 0;
	if (!(*file_name))
		return (1);
	while (*file_name)
	{
		if (!is_blank(*file_name))
			return (0);
		file_name++;
	}
	return (1);
}

int	split_and_check_ambiguity(char *file_name)
{
	int		i;
	int		ret;
	char	**tokens;

	i = 0;
	ret = 0;
	tokens = produce_tokens(file_name, mask_generation2(file_name));
	while (*(tokens + i))
	{
		//printf("%s\n", *(tokens + i));
		i++;
	}
	//printf("%d %s\n", i, *tokens);
	*tokens = ft_strtrim(*tokens, " ");
	*tokens = remove_quotes(*tokens);
	if (i > 1 || !(**tokens))
		ret = 1;
	i = -1;
	while (*(tokens + ++i))
		ft_garbage_collector(SINGLE_RELEASE, 0, *(tokens + i));
	ft_garbage_collector(SINGLE_RELEASE, 0, tokens);
	return (ret);
}

// "a"$space
int	is_ambiguous_redirect(char **ptr_to_file_name)
{
	int		ret;
	char	*file_name;

	ret = 0;
	expand_if(ptr_to_file_name);
	file_name = *ptr_to_file_name;
	if (is_all_blank(file_name))
		ret = 1;
	if (!ret && ft_strchr(file_name, ' '))
		ret = split_and_check_ambiguity(file_name);
	return (ret);
}
//"$a"
//a="a b"