/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:21:46 by okhiar            #+#    #+#             */
/*   Updated: 2023/02/12 11:17:08 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	here_doc(t_cmds *cmds)
{
	char	*line;

	line = readline(HD_MSG);
	while (line && ft_strcmp(line, cmds->delimiter))
	{
		write(cmds->hd_fd, line, ft_strlen(line));
		write(cmds->hd_fd, "\n", 1);
		free(line);
		line = readline(HD_MSG);
	}
	if (line)
		free(line);
	close(cmds->hd_fd);
	return (0);
}