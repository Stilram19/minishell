/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:50:46 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/05 20:40:40 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	global_clean(void)
{
	g = ft_garbage_collector(ALLOCATE, sizeof(t_global), NULL);
	g->here_files = ft_garbage_collector(ALLOCATE, sizeof(t_queue), NULL);
	queue_init(g->here_files);
}

void	restart(void)
{
	ft_garbage_collector(GLOBAL_RELEASE, 0, NULL);
	global_clean();
	sig_set();
}

void	heredoc_clean(void)
{
	t_file	*heredoc;

	//g->exit_status = EXIT_FAILURE;
	while (g->here_files->len)
	{
		heredoc = queue_pop(g->here_files);
		unlink(heredoc->pathname);
		close(heredoc->here_fd);
	}
}
