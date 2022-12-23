/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:54:10 by eusatiko          #+#    #+#             */
/*   Updated: 2022/12/08 17:13:58 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && i + j < len)
		{
			if (little[j + 1] == '\0')
				return ((char *)big + i);
			j++;
		}
		i++;
	}
	return (NULL);
}


#include <stdio.h>
//#include <bsd/string.h>

int main(void)
{
	char *little = "dolor";
	char *big = "lorem ipsum dolor sit amet";

	//printf("strnstrn(big, little, 25) found: %s\n", strnstr(big, little, 25));
	printf("ft_strnstrn(big, little, 25) found: %s\n", ft_strnstr(big, little, 15));
    return 0;
}

