/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:50:46 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/04 17:53:00 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	init_session(void)
{
	struct termios	terminal_sets;
	// printf("\e[1;32m");
	// printf("__       __  ______  __    __  ______   ______   __    __  ________  __        __       \n");
	// printf("|  \\     /  \\|      \\|  \\  |  \\|      \\ /      \\ |  \\  |  \\|        \\|  \\      |  \\      \n");
	// printf("| $$\\   /  $$ \\$$$$$$| $$\\ | $$ \\$$$$$$|  $$$$$$\\| $$  | $$| $$$$$$$$| $$      | $$      \n");
	// printf("| $$$\\ /  $$$  | $$  | $$$\\| $$  | $$  | $$___\\$$| $$__| $$| $$__    | $$      | $$      \n");
	// printf("| $$$$\\  $$$$  | $$  | $$$$\\ $$  | $$   \\$$    \\ | $$    $$| $$  \\   | $$      | $$      \n");
	// printf("| $$\\$$ $$ $$  | $$  | $$\\$$ $$  | $$   _\\$$$$$$\\| $$$$$$$$| $$$$$   | $$      | $$      \n");
	// printf("| $$ \\$$$| $$ _| $$_ | $$ \\$$$$ _| $$_ |  \\__| $$| $$  | $$| $$_____ | $$_____ | $$_____ \n");
	// printf("| $$  \\$ | $$|   $$ \\| $$  \\$$$|   $$ \\ \\$$    $$| $$  | $$| $$     \\| $$     \\| $$     \\\n");
	// printf(" \\$$      \\$$ \\$$$$$$ \\$$   \\$$ \\$$$$$$  \\$$$$$$  \\$$   \\$$ \\$$$$$$$$ \\$$$$$$$$ \\$$$$$$$$\n");
	// printf("\n                                                                         \e[1;34m BY OMAR & OUSSAMA\n\e[0m");
	tcgetattr(STDIN_FILENO, &terminal_sets);
	terminal_sets.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal_sets);
	restart();
}
