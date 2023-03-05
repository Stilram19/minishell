/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:37:32 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/05 16:14:32 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
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
	int	here_flag;

	here_flag = *heredoc;
	if (!here_flag && !ft_strncmp(*tokens, "<<", 2))
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
	if (is_ambiguous_redirect(tokens + 1))
		file->type = AMBIG;
	//printf("%p\n", *(tokens + 1));
	return (1);
}

void	 give_files_types(char **tokens, t_file *files, int len)
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

void	give_files_names(char **tokens, t_file *files, int len)
{
	int		i;
	char	*op;

	i = 0;
	while (i < len)
	{
		((op = NULL) || (files[i].pathname = NULL));
		if (files[i].type == HERE && ++i)
			continue ;
		if (files[i].type == APPEND)
			op = APPEND_STR;
		else if (files[i].type == OUT)
			op = OUT_STR;
		else if (files[i].type == IN)
			op = IN_STR;
		else if (files[i].type == AMBIG)
		 	tokens += 2;
		while (op && *tokens)
		{
			if (ft_strncmp(op, *tokens, ft_strlen(op) + 1) && tokens++)
				continue ;
			tokens++;
			files[i].pathname = unmask_quotes(remove_quotes(*tokens));// ! here
			break ;
		}
		i++;
	}
}

void	files_parsing(t_node *root, char *str)
{
	int			expand_enable;
	t_queue		*limiters;
	t_file		*heredoc;
	char		**tokens;

	if (g->exit_status)
		return ;
	tokens = produce_tokens(str, mask_generation(str));
	root->data.f_count = files_count(tokens);
	root->data.files = ft_garbage_collector(ALLOCATE,
		sizeof(t_file) * root->data.f_count, NULL);
	limiters = get_limiters(tokens, &expand_enable);
	give_files_types(tokens, root->data.files, root->data.f_count);
	give_files_names(tokens, root->data.files, root->data.f_count);
	heredoc = get_here_doc(root->data.files, root->data.f_count);
	if (!heredoc)
		return ;
	heredoc->pathname = random_file_name_generation();
	heredoc->here_fd = open(heredoc->pathname, O_CREAT | O_RDWR | O_TRUNC, 0666);
	queue_push(g->here_files, heredoc);
	ft_heredoc(heredoc->here_fd, limiters, expand_enable);
}
