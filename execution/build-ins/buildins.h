/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 10:31:04 by okhiar            #+#    #+#             */
/*   Updated: 2023/02/10 12:57:10 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDINS_H
# define BUILDINS_H

# include <unistd.h>
# include <stdio.h>

int	ft_cd(char *dir);
int	ft_pwd(void);
int	ft_env(void);

#endif