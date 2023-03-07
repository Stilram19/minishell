/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:39:55 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/07 14:46:32 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*first_op_add(char *str, char *op)
{
	int		quote;
	int		op_len;
	int		parenth;
	char	*cmp_op;

	quote = 0;
	parenth = 0;
	cmp_op = NULL;
	op_len = ft_strlen(op);
	while (*str)
	{
		open_close_quotes(*str, &quote);
		if (!quote)
		{
			open_close_parenth(*str, &parenth);
			cmp_op = get_operator(str);
		}
		if (!quote && !parenth && cmp_op && !ft_strncmp(cmp_op, op, op_len + 1))
			return (str);
		str++;
	}
	return (NULL);
}

/*char	*last_logical_operator(char *str)
{
	char	*or;
	char	*and;

	and = first_op_add(str, AND_STR);
	or = first_op_add(str, OR_STR);
	return (ft_min(and, or));
}*/

char	*last_logical_operator(char *str)
{
	int		quotes;
	int		parenth;
	char	*last_op;

	quotes = 0;
	parenth = 0;
	last_op = NULL;
	while (*str)
	{
		open_close_quotes(*str, &quotes);
		if (!quotes)
			open_close_parenth(*str, &parenth);
		if (!(quotes || parenth) && !(ft_strncmp(str, OR_STR, 2)
			&& ft_strncmp(str, AND_STR, 2)))
			last_op = str;
		str++;
	}
	return (last_op);
}

char	*first_redirec(char *str)
{
	char	*in;
	char	*out;
	char	*here;
	char	*append;

	here = first_op_add(str, HERE_STR);
	append = first_op_add(str, APPEND_STR);
	in = first_op_add(str, IN_STR);
	out = first_op_add(str, OUT_STR);
	in = ft_min(in, here);
	out = ft_min(out, append);
	return (ft_min(in, out));
}

char	*middle_operator(char *str)
{
	char	*middle_op;
	char	*redirec;
	char	*pipe_add;
	char	*logical_op;

	middle_op = NULL;
	logical_op = last_logical_operator(str);
	middle_op = logical_op;
	if (!middle_op)
	{
		pipe_add = first_op_add(str, PIPE_STR);
		middle_op = pipe_add;
	}
	if (!middle_op)
	{
		redirec = first_redirec(str);
		middle_op = redirec;
	}
	return (middle_op);
}

// TODO the input string must be trimed.
void	parse_tree(char *str, t_node *root, int status)
{
	int		op_type;
	char	*op;

	op = middle_operator(str);
	op_type = operator_type(op);
	node_init(root, status);
	if (op_type == AND || op_type == OR || op_type == PIPE)
	{
		root->data.type = op_type;
		root->left = ft_garbage_collector(ALLOCATE, sizeof(t_node), NULL);
		root->right = ft_garbage_collector(ALLOCATE, sizeof(t_node), NULL);
		parse_tree(left_str(str, op), root->left, status);
		parse_tree(right_str(str, op, 0), root->right, status);
	}
	else if (op_type == REDIREC)
	{
		root->data.type = REDIREC;
		root->left = ft_garbage_collector(ALLOCATE, sizeof(t_node), NULL);
		parse_tree(left_str(str, op), root->left, status);
		files_parsing(root, right_str(str, op, 1));
	}
	else if (*str == '(')
		parse_tree(remove_outer_parenth(str), root, root->data.status + 1);
	else
		cmd_parsing(root, str);
}
