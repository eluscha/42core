/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:09:17 by eusatiko          #+#    #+#             */
/*   Updated: 2022/12/29 13:56:05 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if ((char)c == 0)
		return ((char *)s + i);
	return (NULL);
}

/*
#include <stdio.h>
#include <string.h>
int main(int argc, char** argv)
{
	if (argc != 3)
	{
		printf("Usage: ./a.out string_to_search char\n");
		return (1);
	}
	printf("strchr returns %s\n", strchr(argv[1], argv[2][0]));
	printf("pointer is %p\n", strchr(argv[1], argv[2][0]));
	printf("ft_strchr returns %s\n", ft_strchr(argv[1], argv[2][0]));
	printf("pointer is %p\n", ft_strchr(argv[1], argv[2][0]));
	printf("test from francinette: strchr(argv[1], 't' + 256) == s ?\n");
	printf("btw 't' + 256 is just %c\n", 't' + 256);
	printf("%s\n", strchr(argv[1], 't' + 256));
	printf("%s\n", ft_strchr(argv[1], 't' + 256));
	printf("extra test for 1024, which is as char %c\n", 1024);
	printf("strchr returns %s\n", strchr("test", 1024));
	printf("pointer is %p\n", strchr("test", 1024));
	printf("ft_strchr returns %s\n", ft_strchr("test", 1024));
	printf("pointer is %p\n", ft_strchr("test", 1024));
	return (0);
}
*/
