/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_wildcards.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 21:24:30 by okhiar            #+#    #+#             */
/*   Updated: 2023/02/19 21:55:27 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	slice_to_lst(char *str, t_list **head)
// {
// 	t_list	*head;

// }

char	**get_lists(t_list *head)
{
	int		i;
	int		size;
	char	**ret;

	i = 0;
	size = ft_lstsize(head);
	ret = (char **)malloc(sizeof(char *) * (size + 1));
	while (i < size)
	{
		ret[i++] = head->content ;
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

	i = 1;
	sliced_args = NULL;
	while (args[i])
	{
		if (ft_strchr(args[i], '*'))
			ft_lstadd_back(&sliced_args, matched_set(args[i]));
		else
			ft_lstadd_back(&sliced_args, ft_lstnew(args[i]));
		i++;
	}
	ret = get_lists(sliced_args);
	return (ret);
}

int	main(void)
{
	char	*args[5] = {"cat", ".*", "khiar", NULL};
	char	**list;
	list = wildcards_slice(args);
	for (int i = 0; list[i] != NULL; i++)
		printf("%s\n", list[i]);
	// if (pattern_match("f*.c*", "file.fdg"))
	// 	printf("Pattern matching\n");
	// else
	// 	printf("Pattern not matching\n");
	return (0);
}