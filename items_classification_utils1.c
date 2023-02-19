/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items_classification_utils1.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:08:45 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/19 16:42:49 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	files_count(char **tokens)
{
	int	count;
	int	heredoc;

	count = 0;
	heredoc = 0;
	while (*tokens)
	{
		if (!heredoc && !ft_strncmp(*tokens, "<<", 2) && count++)
			heredoc = 1;
		else if (!ft_strncmp(*tokens, "<", 1)
			|| !ft_strncmp(*tokens, ">", 1))
			count++;
		tokens++;
	}
	return (count);
}

void	give_file_type(char **tokens, t_file *file, int *heredoc)
{
	if (!(*heredoc) && !ft_strncmp(*tokens, "<<", 2))
	{
		file->file_type = HEREDOC;
		*heredoc = 1;
		return ;
	}
	if (!ft_strncmp(*tokens, "<", 1))
		file->file_type = IN;
	else if (!ft_strncmp(*tokens, ">>", 2))
		file->file_type = APPEND;
	else if (!ft_strncmp(*tokens, ">", 1))
		file->file_type = OUT;
	if (*(tokens + 1) && !**(tokens + 1))
		file->file_type = AMBIG_REDIREC;
}

void	give_files_types(char **tokens, t_file *files, int len)
{
	int	i;
	int	j;
	int	heredoc;

	i = 0;
	j = len - 1;
	heredoc = 0;
	while (*(tokens + i))
		i++;
	while (i--)
	{
		if (ft_strncmp(*(tokens + i), "<", 1)
			&& ft_strncmp(*(tokens + i), ">", 1))
			continue ;
		give_file_type(tokens + i, files + j, &heredoc);
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
	t_file	*heredoc;

	len = files_count(tokens);
	op->files_count = len;
	if (!len)
		return (NULL);
	ft_garbage_collector(ALLOCATE, sizeof(t_file) * len, NULL);
	give_files_types(tokens, files, len);
	give_files_names(tokens, files);
	heredoc = get_here_doc(files);
	if (!heredoc)
		return (files);
	heredoc->heredoc_fd = open("heredoc", O_CREAT | O_RDWR | O_TRUNC, 0666);//TODO IMPLEMENT A METHOD FOR RANDOM FILENAME GENERATION
	open_heredoc(tokens, heredoc->heredoc_fd);
	return (files);
}
