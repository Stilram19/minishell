/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvp.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 18:15:45 by okhiar            #+#    #+#             */
/*   Updated: 2023/01/31 19:55:55 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXECVP_H
# define FT_EXECVP_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

char	*ft_strjoin(char *str1, char *str2);
char	**ft_split(char *str, char c);
char	*ft_strdup(char *str);

#endif