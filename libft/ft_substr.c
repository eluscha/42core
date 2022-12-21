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

	bflen = ft_strlen(s) - start < len ? ft_strlen(s) - start : len;
	ptr = malloc(bflen + 1);
	if (ptr == 0)
		return (0);
	i = start;
	while (i < bflen + start)
	{
		ptr[i - start] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

/*
#include <stdio.h>
int	main(void)
{
	char	*str = "I am the big string";
	char	*substr = ft_substr(str, 13, 5);

	printf("%s\n", substr);
	return (0);
}
*/