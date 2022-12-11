/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 11:04:19 by eusatiko          #+#    #+#             */
/*   Updated: 2022/12/07 11:45:29 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		while (src[i] != '\0')
			i++;
		return (i);
	}
	while (src[i] != '\0')
	{
		if (i < size - 1)
			dst[i] = src[i];
		i++;
	}
	if (i < size - 1)
		dst[i] = src[i];
	else
		dst[size - 1] = '\0';
	return (i);
}

#include <bsd/string.h>
int	main(void)
{
	char dest[10];
	char src[] = "Hello there, Venus";

	int res = ft_strlcpy(dest, src, 6);
	printf("source was: %s\n", src);
	printf("now in dest is: %s\n", dest);
	printf("return value is %i\n", res);
	return (0);
}
