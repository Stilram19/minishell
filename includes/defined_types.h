/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defined_types.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:29:48 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/04 21:52:12 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINED_TYPES_H
# define DEFINED_TYPES_H

# include "../libft/libft.h"

# define SUCCESS 0

# define OR_STR "||"
# define AND_STR "&&"
# define PIPE_STR "|"
# define IN_STR "<"
# define OUT_STR ">"
# define HERE_STR "<<"
# define APPEND_STR ">>"

# define SINGLE_QUOTE_MASK -1
# define DOUBLE_QUOTE_MASK -2
# define WILDCARD_MASK -3

# define CMN_NF "\e[1;31mMinishell\e[0m: Command not found\n"

# define RED "\e[1;31m"
# define DEFAULT "\e[0m"

# define AMBIG_ERR 1

# define CTRL_C 42

# define SYNTAX_ERROR 258

enum data_type
{
	AND, OR, PIPE, REDIREC, COMMAND
};

enum file_type
{
	IN, OUT, HERE, APPEND, AMBIG
};

enum io_type
{
	DFTERM, PIPE_IO
};

typedef struct s_fdio
{
	int	fd;
	int	type;
}	t_fdio;

typedef struct s_file
{
	int		type;
	int		here_fd;
	char	*pathname;
}t_file;

typedef struct s_data
{
	int		type;
	int		status;
	int		f_count;
	char	*cmd;
	char	**args;
	t_file	*files;
}t_data;

typedef struct s_node
{
	struct s_node	*left;
	struct s_node	*right;
	t_data			data;
}t_node;

typedef struct s_item{
	void			*data;
	struct s_item	*next;
}t_item;

typedef struct s_queue{
	int		len;
	t_item	*first;
	t_item	*last;
}t_queue;

typedef struct s_global
{
	int		exit_status;
	t_queue	*here_files;
}t_global;

t_global	*g;

#endif
