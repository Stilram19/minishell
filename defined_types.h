/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defined_types.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:29:48 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/19 18:27:02 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINED_TYPES_H
# define DEFINED_TYPES_H

# include "../libft/libft.h"

# define SUCCESS 0
# define ERROR 1
# define UPDATE 0
# define CTRL_C 42

enum	e_item_type
{
	L_PARENTH, R_PARENTH, OR, AND, PIPE, OPERAND
};

enum	e_file_type
{
	IN, OUT, HEREDOC, APPEND, AMBIG_REDIREC
};

typedef struct s_balance
{
	char	*stack;
	int		top_i;
}t_balance;

typedef struct s_file
{
	int		file_type;
	int		heredoc_fd;
	char	*name;
}t_file;

typedef struct s_arg
{
	int		flag;
	char	*str;
}t_arg;

typedef struct s_operand
{
	int		files_count;
	int		status;
	char	*cmd;
	t_arg	**args;
	t_file	*files;
}t_operand;

typedef struct s_item
{
	int			type;
	t_operand	*operand;
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
