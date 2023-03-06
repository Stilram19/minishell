/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:50:46 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/06 17:01:50 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	global_init(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	sig_set();
	get_env(env_dup(env));
	g = malloc(sizeof(t_global));
	g->exit_status = EXIT_SUCCESS;
	g->here_files = malloc(sizeof(t_queue));
	queue_init(g->here_files);
}

void	refresh(char *line)
{
	free(line);
	ft_garbage_collector(GLOBAL_RELEASE, 0, NULL);
}

void	heredoc_clean(void)
{
	t_file	*heredoc;

	g->exit_status = EXIT_FAILURE;
	while (g->here_files->len)
	{
		heredoc = queue_pop(g->here_files);
		unlink(heredoc->pathname);
		close(heredoc->here_fd);
	}
}
