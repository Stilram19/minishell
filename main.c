/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obednaou <obednaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:16:56 by obednaou          #+#    #+#             */
/*   Updated: 2023/03/01 18:35:40 by obednaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*first_operator(char *str);
int		operator_type(char *op);

void	test(char *str)
{
	//int		op_type;
	char	*op;
	char	*right;
	char	*left;

	(void)right;
	op = first_operator(str);
	left = left_str(str, op);
	printf("%s\n", left);
	//printf("%s\n", op);
}

int	main(int argc, char **argv, char **env)
{
	(void)env;
	(void)argc;
	test(*(argv + 1));
	return (0);
}
