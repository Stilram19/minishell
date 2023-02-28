/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 10:05:21 by okhiar            #+#    #+#             */
/*   Updated: 2023/02/26 13:58:57 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pattern_match(char *pattern, char *match)
{
	if (!*pattern && !*match)
		return (1);
	if (*pattern == *match)
		return (*match && pattern_match(pattern + 1, match + 1));
	if (*pattern == '*')
		return (pattern_match(pattern + 1, match)
			|| (*match && pattern_match(pattern, match + 1)));
	return (0);
}

int	dir_count(void)
{
	int				count;
	struct dirent	*dir_entry;
	DIR				*dir_ptr;

	dir_ptr = opendir(".");
	if (!dir_ptr)
		return (0);
	count = 0;
	dir_entry = readdir(dir_ptr);
	while (dir_entry)
	{
		count++;
		dir_entry = readdir(dir_ptr);
	}
	closedir(dir_ptr);
	return (count);
}

char	**dir_entry(void)
{
	int				i;
	char			**entry_list;
	struct dirent	*dir_entry;
	DIR				*dir_ptr;
	t_list			*matchlist;

	entry_list = (char **)malloc(sizeof(char *) * (dir_count() + 1));
	dir_ptr = opendir(".");
	i = 0;
	dir_entry = readdir(dir_ptr);
	while (dir_entry)
	{
		entry_list[i] = ft_strdup(dir_entry->d_name);// TODO replace * {00101010} with -1 {11111111} on the dir entry
		i++;
		dir_entry = readdir(dir_ptr);
	}
	entry_list[i] = NULL;
	closedir(dir_ptr);
	return (entry_list);
}

t_list	*matched_set(char *pattern)
{
	int		i;
	t_list	*head;
	char	**dir_set;

	i = 0;
	head = NULL;
	dir_set = dir_entry();
	while (dir_set[i])
	{
		if (pattern_match(pattern, dir_set[i]) && (dir_set[i][0] != '.'
			|| pattern[0] == '.'))
			ft_lstadd_back(&head, ft_lstnew(dir_set[i]));// TODO Replace -1 By * to back to original
		i++;
	}
	return (head);
}

