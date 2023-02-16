/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 13:46:18 by okhiar            #+#    #+#             */
/*   Updated: 2023/02/11 16:51:55 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPERS_H
# define HELPERS_H

#include "../minishell.h"

void	ft_dup2(int f1, int f2);
void	redirect_out(t_cmds *cmds, t_redc *red);
int		here_doc(t_cmds *cmds);

#endif