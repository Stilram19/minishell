/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:39:55 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/26 22:05:27 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	node_init(t_node *root, int status)
{
	root->left = NULL;
	root->right = NULL;
	root->data.args = NULL;
	root->data.cmd = NULL;
	root->data.f_count = 0;
	root->data.files = NULL;
	root->data.status = status;
	root->data.type = COMMAND;
}

int	is_first_operator(char *str, char *op)
{
	int	op_len;
	int	quote;
	int	parenth;

	quote = 0;
	parenth = 0;
	op_len = ft_strlen(op);
	while (*str)
	{
		open_close_quotes(*str, &quote);
		(!quote && open_close_parenth(*str, &parenth));
		if (!(quote || parenth || ft_strncmp(str, op, op_len)))
			return (1);
		str++;
	}
	return (0);
}

int	operator_type(char *op)
{
	if (!op)
		return (-1);
	if (!ft_strncmp(op, AND_STR, 2))
		return (AND);
	if (!ft_strncmp(op, OR_STR, 2))
		return (OR);
	if (!ft_strnmp(op, PIPE_STR, 1))
		return (PIPE);
	return (REDIREC);
}

char	*first_operator(char *str)
{
	if (is_first_operator(str, AND_STR))
		return (AND_STR);
	if (is_first_operator(str, OR_STR))
		return (OR_STR);
	if (is_first_operator(str, PIPE_STR))
		return (PIPE_STR);
	if (is_first_operator(str, IN_STR))
		return (IN_STR);
	if (is_first_operator(str, OUT_STR))
		return (OUT_STR);
	if (is_first_operator(str, HERE_STR))
		return (HERE_STR);
	if (is_first_operator(str, APPEND_STR))
		return (APPEND_STR);
	return (NULL);
}
// TODO the input string must be trimed.
void	parse_tree(char *str, t_node *root, int status)
{
	int		op_type;
	char	*op;

	op = first_operator(str);
	op_type = operator_type(op);
	node_init(root, status);
	if (op_type == AND || op_type == OR || op_type == PIPE)
	{
		root->data.type = op_type;
		root->left = ft_garbage_collector(ALLOCATE, sizeof(t_node), NULL);
		root->right = ft_garbage_collector(ALLOCATE, sizeof(t_node), NULL);
		parse_tree(left_str(str, op), root->left, status);
		parse_tree(right_str(str, op), root->right, status);
	}
	else if (op_type == REDIREC)
	{
		root->data.type = REDIREC;
		root->left = ft_garbage_collector(ALLOCATE, sizeof(t_node), NULL);
		parse_tree(left_str(str, op), root->left, status);
		files_parsing(root, right_str(str, op), op);
	}
	else if (ft_strchr(str, '('))
		parse_tree(remove_outer_parenth(str), root, 1);
	else
		cmd_parsing(root, str);
}
