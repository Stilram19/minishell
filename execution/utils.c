/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:23:18 by okhiar            #+#    #+#             */
/*   Updated: 2023/02/28 15:12:49 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_operand	*command_fill(char *cmd)
{
	t_operand	*cmd_s;

	cmd_s = (t_operand *)malloc(sizeof(t_operand));
	cmd_s->cmd = ft_strdup(cmd);
	cmd_s->args = (char **)malloc(sizeof(char *) * 5);
	cmd_s->args[0] = ft_strdup(cmd);
	cmd_s->args[1] = NULL;
	// printf("%p=====\n", cmd_s->args[0]);
	return (cmd_s);
}

t_files	**files_fill(void)
{
	t_files **files;

	files = (t_files **)malloc(sizeof(t_files *) * 4);
	files[0] = NULL;
	return (files);
}

void	set_exit_status(int status)
{
	char	*var;
	char	**env;

	var = ft_strjoin("?=", ft_itoa(status));
	env = get_env(NULL);
	ft_set_var(env, var, 0);
}

void	_ft_putstr_fd(char *str, int fd, int ext)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	exit(ext);
}

char	*search_replace(char *str, char needle, char replacement)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == needle)
			str[i] = replacement;
		i++;
	}
	return (str);
}