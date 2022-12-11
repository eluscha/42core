/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:21:31 by eusatiko          #+#    #+#             */
/*   Updated: 2022/12/08 14:33:29 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void *ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	size_t	i;

	ptr = (unsigned char*)s;
	i = 0;
	while(i < n)
	{
		if (ptr[i] == (unsigned char)c)
			return (ptr+i);
		i++;
	}
	return (NULL);
}


#include <string.h>
#include <stdio.h>
int main(void)
{
	char src[50] = "Hi i am the source!";

	printf("ft_memchr gives %p\n", ft_memchr(src, 105, 9));
	printf("memchr gives %p\n", memchr(src, 105, 9));

	int arr[] = {0,1,2,3,4,5};	

	printf("ft_memchr gives %p\n", ft_memchr(arr, 1, 8));
	printf("memchr gives %p\n", memchr(arr, 1, 8));
	return (0);
}

