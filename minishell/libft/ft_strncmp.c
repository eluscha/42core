/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:10:01 by eusatiko          #+#    #+#             */
/*   Updated: 2022/12/07 14:13:15 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && i < n)
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	if (i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

/*
#include <string.h>
#include <stdio.h>
int main(void)
{
	char *s1 = "test\200";
	char *s2 = "test\0";

	printf("strncmp(s1, s2, 6) gives %i\n", strncmp(s1, s2, 6));
	printf("ft_strncmp(s1, s2, 6) gives %i\n", ft_strncmp(s1, s2, 6));
}
*/
