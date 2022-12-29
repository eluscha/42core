/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 11:48:56 by eusatiko          #+#    #+#             */
/*   Updated: 2022/12/29 13:41:25 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	ptr = s;
	while (i < n)
	{
		*ptr = (unsigned char)c;
		ptr++;
		i++;
	}
	return (s);
}

/*#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[50];

	strcpy(str,"This is string.h library function");
	puts(str);

	memset(str,'$',7);
	puts(str);

	strcpy(str,"This is string.h library function");
	puts(str);

	ft_memset(str,'$',7);
	puts(str);

	int intar[] = {1, 2, 3, 4};
	memset(intar, '$', 7);
	int i = 0;
	while(i < 4)
	{
		printf("%i ", intar[i]);
		i++;
	}

	printf("\n");
	
	int intar2[] = {1, 2, 3, 4};
	ft_memset(intar2, '$', 7);
	i = 0;
	while(i < 4)
	{
		printf("%i ", intar2[i]);
		i++;
	}

	return(0);
}*/
