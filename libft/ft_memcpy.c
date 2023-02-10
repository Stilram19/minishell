/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 20:23:10 by okhiar            #+#    #+#             */
/*   Updated: 2022/11/05 22:47:10 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (src == dest)
		return (dest);
	while (i < len)
	{
		*((char *) dest + i) = *((char *) src + i);
		i++;
	}
	return (dest);
}


// int main(void)
// {
// 	int arr[2] = {0};
// 	int tab[2] = {259, 1};
// 	ft_memcpy(arr, tab, 1);
// 	for (int i = 0; i < 2; i++)
// 		printf("arr[%d] == %d\n", i, arr[i]);
// 	return (0);
// }

/*

int arr[2] = {0};
int tab[2] = {259, 1};
memcpy(arr, tab, 1);

arr ==> 00000000 00000000 00000000 00000000 00000000 00000000 00000000 0000011 ==> 3

tabb ==> 00000000 00000000 00000000 00000001 | 00000000 00000000 00000001 0000011

*/