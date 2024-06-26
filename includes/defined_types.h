/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defined_types.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:29:48 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/09 01:02:39 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINED_TYPES_H
# define DEFINED_TYPES_H

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

# define CTRL_C 42

# define VALID_SYNTAX 0
# define SYNTAX_ERROR 258

# define RED_BOLD "\e[1;31m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define RESET "\e[0m"

enum e_data_type
{
	AND,
	OR,
	PIPE,
	REDIREC,
	COMMAND
};

enum e_file_type
{
	IN,
	OUT,
	HERE,
	APPEND,
	AMBIG
};

enum e_io_type
{
	P_EXEC,
	C_EXEC,
	SUB_EXEC
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
	int		sig_flag;
	int		exit_status;
	t_queue	*here_files;
}t_global;

extern t_global	*g_global;

#endif
