/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:33:58 by eusatiko          #+#    #+#             */
/*   Updated: 2022/12/29 13:40:06 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (ptr1[i] < ptr2[i])
			return (-1);
		else if (ptr1[i] > ptr2[i])
			return (1);
		i++;
	}
	return (0);
}

/*
#include <stdio.h>
#include <string.h>
int main(void)
{
	char str1[] = "Hello i love you";
	char str2[] = "Hello hi bye";

	printf("memcmp returns %i\n", memcmp(str1, str2, 7));
	printf("ft_memcmp returns %i\n", ft_memcmp(str1, str2, 7));

	int arr1[] = {1, -1, -2};
	int arr2[] = {1, -1, -1};
	
	printf("memcmp returns %i\n", memcmp(arr1, arr2, 9));
	printf("ft_memcmp returns %i\n", ft_memcmp(arr1, arr2, 9));

	return (0);
}
*/
