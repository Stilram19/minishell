/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:50:46 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/09 01:02:59 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_shell_level(void)
{
	char	*shlvl;
	int		int_val;

	shlvl = get_var_value("SHLVL");
	if (!shlvl)
		return ;
	int_val = ft_atoi(shlvl);
	int_val++;
	ft_set_var(get_env(NULL), ft_strjoin("SHLVL=", ft_itoa(int_val)), 0);
}

void	global_init(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	sig_set();
	get_env(env_dup(env));
	g_global = malloc(sizeof(t_global));
	g_global->exit_status = EXIT_SUCCESS;
	g_global->sig_flag = 0;
	set_exit_status(g_global->exit_status);
	g_global->here_files = malloc(sizeof(t_queue));
	queue_init(g_global->here_files);
	set_shell_level();
}

void	refresh(char *line)
{
	free(line);
	g_global->sig_flag = 0;
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
