/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:09:17 by eusatiko          #+#    #+#             */
/*   Updated: 2022/12/29 10:16:07 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strchr(const char *s, int c)
{
	int i;
	
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)s+i);
		i++;
	}
	if (s[i] == c)
		return ((char *)s+i);
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
	printf("%s\n", strchr(argv[1], argv[2][0]));
	printf("%s\n", ft_strchr(argv[1], argv[2][0]));
	printf("test from francinette: strchr(argv[1], 't' + 256) == s ?\n");
	printf("btw 't' + 256 is just %c\n", 't' + 256);
	printf("%s\n", strchr(argv[1], 't' + 256));
	printf("%s\n", ft_strchr(argv[1], 't' + 256));
	return (0);
}
*/
