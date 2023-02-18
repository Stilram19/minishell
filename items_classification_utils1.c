/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items_classification_utils1.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:08:45 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/18 18:50:51 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	files_count(char **tokens)
{
	int	count;

	count = 0;
	while (*tokens)
	{
		if (!ft_strncmp(*tokens, "<", 1)
			|| !ft_strncmp(*tokens, ">", 1))
			count++;
		tokens++;
	}
	return (count);
}

void	give_file_type()

void	give_files_types(char **tokens, t_file *files, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*(tokens + i))
		i++;
	while (i--)
	{
		if (ft_strncmp(*tokens, "<", 1)
			&& ft_strncmp(*tokens, ">", 1))
			continue ;	
		give_file_type(files + j);
		j--;
	}
}

void	give_files_names(char **tokens, t_file *files)
{
	while (*tokens)
	{
		if (ft_strncmp(*tokens, "<\0", 2)
			&& ft_strncmp(*tokens, ">", 1) && tokens++)
			continue ;
		if (files->file_type != AMBIG_REDIREC && tokens++)
		{
			files->name = remove_quotes(*tokens);
			continue ;
		}
		tokens++;
		files->name = NULL;
	}
}

t_file	*get_files(char **tokens, t_operand *op)
{
	int		len;
	t_file	*files;

	len = files_count(tokens);
	op->files_count = len;
	if (!len)
		return (NULL);
	ft_garbage_collector(ALLOCATE, sizeof(t_file) * len, NULL);
	give_files_types(tokens, files);
	give_files_names(tokens, files);
	open_heredoc_if(tokens, files);
	return (files);
}
