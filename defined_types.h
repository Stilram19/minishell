/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defined_types.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:29:48 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/15 17:28:39 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINED_TYPES_H
# define DEFINED_TYPES_H

# include "../libft/libft.h"

# define SUCCESS 0
# define ERROR 1
# define UPDATE 0

typedef struct s_balance
{
	char	*stack;
	int		top_i;
}t_balance;

#endif