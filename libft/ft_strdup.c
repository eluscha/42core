/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 11:20:41 by eusatiko          #+#    #+#             */
/*   Updated: 2022/12/29 13:42:27 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char		*ptr;
	size_t		i;
	size_t		len;

	len = ft_strlen(s);
	ptr = malloc(len + 1);
	if (ptr == 0)
		return (0);
	i = 0;
	while (i < len + 1)
	{
		ptr[i] = s[i];
		i++;
	}
	return (ptr);
}

/*
#include <stdio.h>
#include <string.h>
int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: ./a.out \"string to be copied\"\n");
		return (1);
	}
	printf("argv[1] pointer is %p\n", argv[1]);
	char *ptr = strdup(argv[1]);
	printf("strdup(str) returns a pointer %p to: %s\n", ptr, ptr);
	char *ptr2 = ft_strdup(argv[1]);
	printf("ft_strdup(str) returns a pointer %p to: %s\n", ptr2, ptr2);
	free(ptr);
	free(ptr2);
	return (0);
}
*/
