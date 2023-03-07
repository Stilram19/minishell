/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_wildcards.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 21:24:30 by okhiar            #+#    #+#             */
/*   Updated: 2023/03/07 16:58:53 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_lists(t_list *head)
{
	int		i;
	int		size;
	char	**ret;

	i = 0;
	size = ft_lstsize(head);
	ret = ft_garbage_collector(ALLOCATE, sizeof(char *) * (size + 1), NULL);
	while (i < size)
	{
		ret[i++] = ft_strdup(head->content);
		head = head->next;
	}
	ret[i] = NULL;
	return (ret);
}

char	**wildcards_slice(char **args)
{
	int		i;
	t_list	*sliced_args;
	char	**ret;

	i = 0;
	sliced_args = NULL;
	while (args[i])
	{
		if (ft_strchr(args[i], '*'))
			ft_lstadd_back(&sliced_args, matched_set(args[i]));
		else
			ft_lstadd_back(&sliced_args, \
			ft_lstnew(ft_strdup1(search_replace(args[i], WILDCARD_MASK, '*'))));
		i++;
	}
	ret = get_lists(sliced_args);
	ft_lstclear(&sliced_args, free);
	return (ret);
}
