/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items_classification_utils2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:57:52 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/19 18:07:47 by obednaou         ###   ########.fr       */
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

void	get_limiters(char **tokens, t_queue *limiters, int *expand_enable)
{
	int	i;
	int	first;

	i = 0;
	first = 1;
	*expand_enable = 1;
	while (*(tokens + i))
		i++;
	queue_init(&limiters);
	while (i--)
	{
		if (!ft_strncmp(*(tokens + i), "<<", 2))
		{
			if (first && (ft_strchr(*(tokens + i + 1), '\'')
					|| ft_strchr(*(tokens + i + 1), '\"')))
				*expand_enable = 0;
			first = 0;
			queue_push(remove_quotes(*(tokens + i + 1)));
		}
	}
}

char	*here_doc_expand(char *line, int expand_enable)
{
	int	i;

	i = 0;
	if (!expand_enable)
		return (line);
	while (*(line + i))
	{
		if (*(line + i) != '$' && ++i)
			continue ;
		if (++i && !ft_isalnum(*(line + i)) && *(line + i) != '?'
			&& *(line + i) != '_')
			continue ;
		line = var_expansion(&line, &i, var_name_len(line + i));
	}
}

void	heredoc_child(char *curr_lim, int fd, int write_enable)
{
	char	*line;

	line = readline("> ");
	while (line)
	{
		if (!ft_strncmp(line, curr_lim, ft_strlen(line) + 1))
			break ;
		if (write_enable)
			ft_putendl_fd(here_doc_expand(line, write_enable - 1), fd);
		free(line);
		line = readline("> ");
	}
	exit(EXIT_SUCCESS);
}

void	open_heredoc(char **tokens, int fd)
{
	int		fd;
	int		expand_enable;
	int		write_enable;
	t_queue	limiters;

	get_limiters(tokens, &limiters, &expand_enable);
	while (!limiters.len)
	{
		write_enable = (limiters.len == 1);
		if (write_enable)
			write_enable += expand_enable;
		sig_def();
		if (!fork())
			heredoc_child((char *)queue_first(limiters), fd, write_enable);
		sig_set();
		wait(NULL);
		ft_garbage_collector(SINGLE_RELEASE, 0, queue_pop(&limiters));
	}
}
