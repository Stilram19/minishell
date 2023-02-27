/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:37:32 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/27 16:10:29 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// R file R file R file
// R file(non expandable) case1
// R file(expandable) case2

//case1: if the file is not expandable-->remove quotes-->you have the name
//case2: the file is expandable-->

// var="hello"
// >> ' '-$var
//'B'cccccc

// var="' '"
// >> $var-hello
// cbcccccc

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
		file->type = HERE;
		*heredoc = 1;
		return (1);
	}
	else if (!ft_strncmp(*tokens, "<<", 2))
		return (0);
	if (!ft_strncmp(*tokens, "<", 1))
		file->type = IN;
	else if (!ft_strncmp(*tokens, ">>", 2))
		file->type = APPEND;
	else if (!ft_strncmp(*tokens, ">", 1))
		file->type = OUT;
	if (is_ambiguous_redirect(*(tokens + 1)))
		file->type = AMBIG;
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
		if (ft_strncmp(*tokens, "<", 2)
			&& ft_strncmp(*tokens, ">", 1) && tokens++)
			continue ;
		if (files->type != AMBIG && tokens++)
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

void	files_parsing(t_node *root, char *str)
{
	char	**tokens;

	tokens = produce_tokens(str, mask_genenration(str));
	root->data.f_count = files_count(tokens);
	root->data.files = ft_garbage_collector(ALLOCATE,
		sizeof(t_file) * root->data.f_count, NULL);
	give_files_types();
}
