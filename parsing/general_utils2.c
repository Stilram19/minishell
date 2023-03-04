/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:08:25 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/04 14:14:23 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_min(void *add1, void *add2)
{
	if (!add1)
		return (add2);
	if (!add2)
		return (add1);
	if (add1 < add2)
		return (add1);
	return (add2);
}

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

int	operator_type(char *op)
{
	if (!op)
		return (-1);
	if (!ft_strncmp(op, AND_STR, 2))
		return (AND);
	if (!ft_strncmp(op, OR_STR, 2))
		return (OR);
	if (!ft_strncmp(op, PIPE_STR, 1))
		return (PIPE);
	return (REDIREC);
}

char	*get_operator(char *op)
{
	if (!ft_strncmp(op, AND_STR, 2))
		return (AND_STR);
	if (!ft_strncmp(op, OR_STR, 2))
		return (OR_STR);
	if (!ft_strncmp(op, PIPE_STR, 1))
		return (PIPE_STR);
	if (!ft_strncmp(op, HERE_STR, 2))
		return (HERE_STR);
	if (!ft_strncmp(op, APPEND_STR, 2))
		return (APPEND_STR);
	if (!ft_strncmp(op, IN_STR, 1))
		return (IN_STR);
	if (!ft_strncmp(op, OUT_STR, 1))
		return (OUT_STR);
	return (NULL);
}
