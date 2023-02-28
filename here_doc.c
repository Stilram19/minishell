/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 20:14:47 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/28 18:22:28 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_file	*get_here_doc(t_file *files, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (files[i].type == HERE)
			return (files + i);
		i++;
	}
	return (NULL);
}

t_queue	*get_limiters(char **tokens, int *expand_enable)
{
	int		i;
	int		last;
	t_queue	*limiters;

	i = 0;
	last = 1;
	*expand_enable = 1;
	limiters = ft_garbage_collector(ALLOCATE, sizeof(t_queue), NULL);
	queue_init(limiters);
	while (*(tokens + i))
		i++;
	while (i--)
	{
		if (!ft_strncmp(*(tokens + i), "<<", 2))
		{
			if (last && (ft_strchr(*(tokens + i + 1), '\'')
					|| ft_strchr(*(tokens + i + 1), '\"')))
				*expand_enable = 0;
			last = 0;
			queue_push(limiters, remove_quotes(*(tokens + i + 1)));
		}
	}
	return (limiters);
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
	return (line);
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

void	heredoc(char **tokens, int fd, t_queue *limiters, int expand)
{
	int		pid;
	int		status;
	int		write_enable;

	while (limiters->len)
	{
		write_enable = (limiters->len == 1);
		if (write_enable)
			write_enable += expand;
		signal(SIGINT, SIG_IGN);
		if (!fork())
		{
			signal(SIGINT, heredoc_sig_handler);
			heredoc_child((char *)queue_first(limiters), fd, write_enable);
		}
		waitpid(pid, &status, 0);
		sig_set();
		if (!WIFEXITED(status) || WEXITSTATUS(status) == CTRL_C)
		{
			heredoc_clean();
			return ;
		}
		ft_garbage_collector(SINGLE_RELEASE, 0, queue_pop(limiters));
	}
	close(fd);
}
