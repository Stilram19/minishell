/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:37:32 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/27 14:09:25 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// R file R file R file
// <<, lim, >, file, <, file, >>, file

int	files_count(char **tokens)
{
	int	count;
	int	heredoc;

	count = 0;
	heredoc = 0;
	while (*tokens)
	{
		
	}
}

void	files_parsing(t_node *root, char *str)
{
	char	**tokens;

	tokens = produce_tokens(str, mask_genenration(str));
	root->data.f_count = files_count(tokens);
}