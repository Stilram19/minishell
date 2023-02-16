/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_tree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:54:16 by okhiar            #+#    #+#             */
/*   Updated: 2023/02/15 17:56:36 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tree	*new_node(int op_type, t_cmds *cmds)
{
	t_tree	*child_node;

	child_node = (t_tree *)malloc(sizeof(t_tree));
	child_node->cmd = cmds;
	// printf("%p-------\n", cmds);
	child_node->operation = op_type;
	child_node->left = NULL;
	child_node->right = NULL;
	return (child_node);
}