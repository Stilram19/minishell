/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_parse_tree.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 13:29:52 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/03 16:53:32 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_files(t_data data)
{
	int	i;

	i = 0;
	printf("Files: {");
	while (i < data.f_count)
	{
		if (data.files[i].type == IN)
			printf("IN:%s", data.files[i].pathname);
		else if (data.files[i].type == OUT)
			printf("OUT:%s", data.files[i].pathname);
		else if (data.files[i].type == APPEND)
			printf("APPEND:%s", data.files[i].pathname);
		else if (data.files[i].type == HERE)
			printf("HERE:%s", data.files[i].pathname);
		else if (data.files[i].type == AMBIG)
			printf("AMBIG");
		else
			printf("ERROR\n");
		if (++i && i < data.f_count)
			printf(", ");
	}
	printf("}\n");
}

void	display_command(t_data data)
{
	char	*status;
	char	**args;

	if (data.status)
		status = "child";
	else
		status = "Parent";
	args = data.args;
	printf("cmd:{%s, %s} ", data.cmd, status);
	printf("args:{");
	while (*args)
	{
		printf("%s", *args);
		if (++args && *args)
			printf(", ");
	}
	printf("}\n");
}

void	display_node_data(t_data data, int indent_level)
{
	while (indent_level--)
		printf("\t");
	if (data.type == OR)
		printf("||\n");
	else if (data.type == AND)
		printf("&&\n");
	else if (data.type == PIPE)
		printf("|\n");
	else if (data.type == REDIREC)
		display_files(data);
	else if (data.type == COMMAND)
		display_command(data);
	else
		printf("ERROR\n");
}

void	display_tree(t_node	*root, int indent_level)
{
	if (!root)
		return ;
	display_node_data(root->data, indent_level);
	display_tree(root->left, indent_level + 1);
	display_tree(root->right, indent_level + 1);
}
