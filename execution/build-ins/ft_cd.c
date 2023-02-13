/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 10:30:31 by okhiar            #+#    #+#             */
/*   Updated: 2023/02/13 14:23:43 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

void	ft_putstr_fd__(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		write(fd, &str[i++], 1);
}

int	ft_cd(char *dir)
{
	if (chdir(dir))
	{
		ft_putstr_fd__("cd: no such file or directory\n", 2);
		return (EXIT_FAILURE);
	}
	// if (ft_strcmp(dir, ".") && ft_strcmp(dir, ".."))
	// 	ft_pwd();
	return (EXIT_SUCCESS);
}