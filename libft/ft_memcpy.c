/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 09:32:45 by eusatiko          #+#    #+#             */
/*   Updated: 2022/12/07 10:19:17 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char* ptr_to;
	unsigned char* ptr_from;

	ptr_to = dest;
	ptr_from = (unsigned char*)src;
	while (n--)
		ptr_to[n] = ptr_from[n];
	return (dest);
}

/*
#include <string.h>
#include <stdio.h>
int main(void)
{
	char src[50] = "Hi i am the source!";
	char dest[50] = "\0\0\0\0\0\0\0\0\0\0";

	ft_memcpy(dest, src, 9);
	printf("%s\n", src);
	printf("%s\n", dest);

	int arr[] = {0,1,2,3,4,5};	
	int arr_dest[] = {-1, -1, -1, -1, -1, -1};

	ft_memcpy(arr_dest, arr, 9);
	int i = 0;
	while(i < 6)
		printf("%i ", arr[i++]);
	printf("\n");
	i = 0;	
	while(i < 6)
		printf("%i ", arr_dest[i++]);
	return (0);
}
*/
