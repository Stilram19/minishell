/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:50:46 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/28 18:09:25 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	global_clean(void)
{
	g = ft_garbage_collector(ALLOCATE, sizeof(t_global), NULL);
	g->here_files = ft_garbage_collector(ALLOCATE, sizeof(t_queue), NULL);
	queue_init(g->here_files);
	g->exit_status = EXIT_SUCCESS;
}

void	restart(char **env)
{
	ft_garbage_collector(GLOBAL_RELEASE, 0, NULL);
	get_env(env_dup(env));
	global_clean();
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
