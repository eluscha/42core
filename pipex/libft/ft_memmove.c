/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 10:19:37 by eusatiko          #+#    #+#             */
/*   Updated: 2022/12/29 13:45:07 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr_to;
	unsigned char	*ptr_from;

	if (!dest && !src)
		return (dest);
	ptr_to = dest;
	ptr_from = (unsigned char *)src;
	if (src < dest)
	{
		while (n--)
			ptr_to[n] = ptr_from[n];
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}

/*
#include <stdio.h>
#include <string.h>
int main(void)
{
	char src[50] = "Hi i am the source!";

	ft_memmove(src+5, src, 9);
	printf("%s\n", src);

	int arr[] = {0,1,2,3,4,5};	

	ft_memmove(arr+4, arr, 8);
	int i = 0;
	while(i < 6)
		printf("%i ", arr[i++]);
	return (0);
}
*/
