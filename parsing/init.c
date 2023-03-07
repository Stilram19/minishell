/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:50:46 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/07 18:22:26 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	global_init(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	sig_set();
	get_env(env_dup(env));
	g_global = malloc(sizeof(t_global));
	g_global->exit_status = EXIT_SUCCESS;
	g_global->here_files = malloc(sizeof(t_queue));
	queue_init(g_global->here_files);
}

void	refresh(char *line)
{
	free(line);
	ft_garbage_collector(GLOBAL_RELEASE, 0, NULL);
}

void	heredoc_clean(int status)
{
	t_file	*heredoc;

	g_global->exit_status = status;
	while (g_global->here_files->len)
	{
		heredoc = queue_pop(g_global->here_files);
		unlink(heredoc->pathname);
		close(heredoc->here_fd);
	}
}
