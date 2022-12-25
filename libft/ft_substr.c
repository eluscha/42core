/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 12:51:22 by eusatiko          #+#    #+#             */
/*   Updated: 2022/12/10 13:44:15 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	bflen;
	size_t	i;

	if (ft_strlen(s) <= start)
		return ("");
	bflen = ft_strlen(s) - start < len ? ft_strlen(s) - start : len;
	ptr = malloc(bflen + 1);
	if (ptr == NULL)
		return (NULL);
	i = start;
	while (i < bflen + start)
	{
		ptr[i - start] = s[i];
		i++;
	}
	ptr[i - start] = '\0';
	return (ptr);
}

/*
#include <string.h>
#include <stdio.h>
int	main(void)
{
	char *str = "01234";
 	size_t size = 10;
 	char *ret = ft_substr(str, 10, size);
 
 	printf("strncmp of result and empty string returns %i\n", strncmp(ret, "", 1));
	
	//char str[] = "i just want this part #############";
 	//size_t size = 20;
 	//char *ret = ft_substr(str, 5, size);
	//printf("result is %s\n", ret);
 	//str[size + 5] = 0;
 	//printf("memcmp gives %i\n", memcmp(ret, str + 5, size + 1));
	return (0);
}
*/
