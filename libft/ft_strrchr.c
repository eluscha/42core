/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:00:50 by eusatiko          #+#    #+#             */
/*   Updated: 2022/12/07 14:07:01 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strrchr(const char *s, int c)
{
	int i;
	
	i = 0;
	while (s[i] != '\0')
		i++;
	if (c == 0)
		return ((char *)s+i);
	while (i >= 0)
	{
		if (s[i] == c)
			return ((char *)s+i);
		i--;
	}
	return (NULL);
}

/*
#include <stdio.h>
#include <string.h>
int main(int argc, char** argv)
{
	if (argc != 3)
		printf("Usage: ./a.out string_to_search char\n");
	printf("%s\n", strrchr(argv[1], argv[2][0]));
	printf("%s\n", ft_strrchr(argv[1], argv[2][0]));
	return (0);
}
*/
