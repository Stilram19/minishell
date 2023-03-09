/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:33:47 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/09 00:54:42 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_global->exit_status = EXIT_FAILURE;
		set_exit_status(g_global->exit_status);
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	heredoc_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		exit(CTRL_C);
	}
}

int	here_sig(void)
{
	signal(SIGINT, heredoc_sig_handler);
	return (1);
}

void	sig_set(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
}

void	sig_def(void)
{
	signal(SIGTSTP, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
