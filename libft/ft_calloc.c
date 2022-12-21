/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 10:19:26 by eusatiko          #+#    #+#             */
/*   Updated: 2022/12/10 10:54:06 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	i;

	ptr = malloc(nmemb * size);
	i = 0;
	while (i < nmemb * size)
	{
		*((char *)ptr + i) = 0;
		i++;
	}
	return (ptr);
}

/*
#include <stdio.h>
#include <string.h>
int main(void)
{
	char *ptr = ft_calloc(10, 4);
	printf("%p\n", ptr);
	char *ptr2 = calloc(10, 4);
	printf("%p\n", ptr2);
	printf("memcmp for ptr and ptr2 gives %i\n", memcmp(ptr, ptr2, 40));
	free(ptr);
	free(ptr2);
	return (0);
}
*/