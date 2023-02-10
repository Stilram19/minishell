/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:49:06 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/10 15:33:39 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "readline/readline.h"

int	main(int ac, char **av, char **env)
{
	get_env(env_dup(env));
	char *user = get_env_var("HOME");
	printf("user: %s\n", user);
	(void)ac;
	(void)av;
	return (0);
}