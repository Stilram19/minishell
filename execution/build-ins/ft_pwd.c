/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 10:43:29 by okhiar            #+#    #+#             */
/*   Updated: 2023/02/10 10:47:29 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putstr_fd(2, "Error occurred while getting the current working directory\n");
		return (1);
	}
	printf("%s\n", cwd);
	return (0);
}