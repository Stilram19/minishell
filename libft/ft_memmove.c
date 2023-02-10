/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhiar <okhiar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 20:58:11 by okhiar            #+#    #+#             */
/*   Updated: 2022/10/18 18:27:55 by okhiar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	if (dest < src)
		ft_memcpy(dest, src, len);
	else if (dest > src)
	{
		while (len--)
			*((char *)dest + len) = *((char *)src + len);
	}
	return (dest);
}
