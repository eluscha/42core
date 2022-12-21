/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:09:17 by eusatiko          #+#    #+#             */
/*   Updated: 2022/12/07 13:49:42 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strchr(const char *s, int c)
{
	int i;
	
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
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
		printf("Usage: ./a.out string_to_search char\n");
	printf("%s\n", strchr(argv[1], argv[2][0]));
	printf("%s\n", ft_strchr(argv[1], argv[2][0]));
	return (0);
}
*/