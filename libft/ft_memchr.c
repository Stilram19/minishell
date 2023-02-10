/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:40:44 by okhiar            #+#    #+#             */
/*   Updated: 2022/11/05 22:47:06 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	const char	*ptr;
	size_t		i;

	i = 0;
	ptr = str;
	if (n)
	{
		while (i < n)
		{
			if ((unsigned char)ptr[i] == (unsigned char)c)
				return ((void *)ptr + i);
			i++;
		}
	}
	return (0);
}


// int main(void)
// {
// 	int arr[2] = {4, -159};
// 	void *ptr = ft_memchr(arr, 255, 8);

// 	printf("%p\n%p", ptr, (char *)&arr[1] + 1);
// 	return (0);
// }

/*

int arr[2] = {4, -159};
void *ptr = ft_memchr(arr, 'a', 8);

arr ==> 11111111 11111111 11111111 01100001 | 00000000 00000000 00000000 00000100

a ==> 97 ==> 01100001
*/