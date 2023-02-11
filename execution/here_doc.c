/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:21:46 by okhiar            #+#    #+#             */
/*   Updated: 2023/02/11 17:19:23 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	here_doc(t_cmds *cmds)
{
	char	*line;

	line = readline(HD_MSG);
	while (line && ft_strcmp(line, cmds->delimiter))
	{
		write(cmds->fdout, line, ft_strlen(line));
		write(cmds->fdout, "\n", 1);
		line = readline(HD_MSG);
	}
	// dup2(cmds->fdout, 0);
	return (cmds->fdout);
}