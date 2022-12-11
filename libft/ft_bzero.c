/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 08:53:18 by eusatiko          #+#    #+#             */
/*   Updated: 2022/12/07 09:30:43 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void *ft_bzero(void *s, size_t n)
{
	unsigned char* ptr;

	ptr = s;
	while (n)
		ptr[--n] = '\0';
	return (s);
}

/*
#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[50];

	strcpy(str,"This is string.h library function");
	puts(str);

	bzero(str+5,1);
	puts(str);

	strcpy(str,"This is string.h library function");
	puts(str);

	ft_bzero(str+5,1);
	puts(str);

	int intar[] = {1, 2, 3, 4};
	bzero(intar, 7);
	int i = 0;
	while(i < 4)
		printf("%i ", intar[i++]);

	printf("\n");
	
	int intar2[] = {1, 2, 3, 4};
	ft_bzero(intar2, 7);
	i = 0;
	while(i < 4)
		printf("%i ", intar2[i++]);

	return(0);
}*/
