/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defined_types.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:29:48 by obednaou          #+#    #+#             */
/*   Updated: 2023/02/09 17:41:07 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINED_TYPES_H
# define DEFINED_TYPES_H

# define SUCCESS 0
# define ERROR 1

typedef struct s_list
{
	void			*data;
	struct s_list	*next;
}					t_list;

#endif