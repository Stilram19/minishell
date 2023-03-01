/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_tree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:54:16 by okhiar            #+#    #+#             */
/*   Updated: 2023/02/28 15:07:44 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tree	*new_node(int op_type, t_operand *cmds, t_files **files)
{
	t_tree	*child_node;

	child_node = (t_tree *)malloc(sizeof(t_tree));
	child_node->item = (t_item *)malloc(sizeof(t_item));
	// printf("%p-------\n", cmds);
	child_node->item->operand = cmds;
	child_node->item->type = op_type;
	child_node->item->files = files;
	child_node->left = NULL;
	child_node->right = NULL;
	return (child_node);
}