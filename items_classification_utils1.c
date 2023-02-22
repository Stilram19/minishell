/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items_classification_utils1.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:08:45 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/22 15:11:37 by obednaou         ###   ########.fr       */
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
		if (!heredoc && !ft_strncmp(*tokens, "<<", 2) && ++count)
			heredoc = 1;
		else if (!ft_strncmp(*tokens, "<<", 2) && tokens++)
			continue ;
		else if (!ft_strncmp(*tokens, "<", 1)
			|| !ft_strncmp(*tokens, ">", 1))
			count++;
		tokens++;
	}
	return (count);
}

int	give_file_type(char **tokens, t_file *file, int *heredoc)
{
	if (!(*heredoc) && !ft_strncmp(*tokens, "<<", 2))
	{
		file->file_type = HEREDOC;
		*heredoc = 1;
		return (1);
	}
	else if (!ft_strncmp(*tokens, "<<", 2))
		return (0);
	if (!ft_strncmp(*tokens, "<", 1))
		file->file_type = IN;
	else if (!ft_strncmp(*tokens, ">>", 2))
		file->file_type = APPEND;
	else if (!ft_strncmp(*tokens, ">", 1))
		file->file_type = OUT;
	if (*(tokens + 1) && !**(tokens + 1))
		file->file_type = AMBIG_REDIREC;
	return (1);
}

void	give_files_types(char **tokens, t_file *files, int len)
{
	int	i;
	int	j;
	int	heredoc;
	int	boolean;

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
		boolean = give_file_type(tokens + i, files + j, &heredoc);
		if (boolean)
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
			files++;
			continue ;
		}
		tokens++;
		files->name = NULL;
		files++;
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
	files = ft_garbage_collector(ALLOCATE, sizeof(t_file) * len, NULL);
	give_files_types(tokens, files, len);
	give_files_names(tokens, files);
	heredoc = get_here_doc(files, len);
	if (!heredoc)
		return (files);
	heredoc->heredoc_fd = open("heredoc",
			O_CREAT | O_RDWR | O_TRUNC, 0666);
	open_heredoc(tokens, heredoc->heredoc_fd);
	return (files);
}
