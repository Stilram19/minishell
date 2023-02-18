/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items_classification_utils2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:57:52 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/18 20:52:59 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_file	*get_here_doc(t_file *files, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (files[i].file_type == HEREDOC)
			return (files + i);
		i++;
	}
	return (NULL);
}

void	get_limiters(char **tokens, t_queue *limiters)
{
	while (*tokens)
	{
		if (!ft_strncmp(*tokens, "<<", 2))
			queue_push(remove_quotes(*(tokens + 1)));
		tokens++;
	}
}

int open_heredoc(char **tokens, t_file *files)
{
	int		fd;
	int		len;
	char	*line;
	t_queue	lines;
	t_queue	limiters;

	get_limiters(tokens, &limiters);
	fd = open("heredoc", O_CREAT | O_RDWR | O_TRUNC, 0666);//TODO IMPLEMENT A METHOD FOR RANDOM FILENAME GENERATION
	line = readline("> ");
	while (queue_first(&lines))
	{
		queue_push(&lines, line);
		len = ft_strlen(line);
		if (ft_strncmp(line, queue_first(&limiters), len + 1))
		else if (!queue_pop(&limiters))
			break ;
		
	}
}
