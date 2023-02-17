/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defined_types.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:29:48 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/17 20:31:03 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINED_TYPES_H
# define DEFINED_TYPES_H

# include "../libft/libft.h"

# define SUCCESS 0
# define ERROR 1
# define UPDATE 0

enum	e_item_type
{
	L_PARENTH, R_PARENTH, OPERAND, OPERATOR
};

enum	e_file_type
{
	IN, OUT
};

typedef struct s_balance
{
	char	*stack;
	int		top_i;
}t_balance;

typedef struct s_file
{
	char	*name;
	int		file_type;
}t_file;

typedef struct s_cmd
{
	int		heredoc_fd;
	char	*cmd;
	char	**args;
	t_file	*files;
}t_cmd;

typedef struct s_item
{
	int			type;
	t_cmd		operand;
}t_item;

typedef struct s_node{
	void			*data;
	struct s_node	*next;
}t_node;

typedef struct s_queue{
	int		len;
	t_node	*first;
	t_node	*last;
}t_queue;

#endif
