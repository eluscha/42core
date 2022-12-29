/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 11:46:45 by eusatiko          #+#    #+#             */
/*   Updated: 2022/12/29 13:44:10 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	destlen;
	size_t	srclen;
	size_t	i;

	destlen = ft_strlen(dst);
	srclen = ft_strlen((char *)src);
	if (size <= destlen)
		return (srclen + size);
	i = 0;
	while (src[i] != '\0' && (destlen + i) < (size - 1))
	{
		dst[destlen + i] = src[i];
		i++;
	}
	dst[destlen + i] = '\0';
	return (destlen + srclen);
}

/*
#include <stdio.h>
#include <bsd/string.h>
#define SIZE 34
int main(void)
{
	char dest[SIZE] = "This is ";
	char dest1[SIZE] = "This is ";
	char src[] = "a potentially long string";
 	size_t res = ft_strlcat(dest, src, SIZE);
 	size_t res1 = ft_strlcat(dest1, src, SIZE);
	printf("strlcat makes dest1: %s\nreturnes: %zu\n", dest1, res1);
	printf("ft_strlcat makes dest: %s\nreturnes: %zu\n", dest, res);
	if (res > SIZE - 1)
		printf("ft_strlcat - String truncated\n");
	else
		printf("ft_strlcat - String was fully copied and concatenated\n");
}
*/
