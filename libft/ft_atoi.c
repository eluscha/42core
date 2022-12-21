/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:15:12 by eusatiko          #+#    #+#             */
/*   Updated: 2022/12/10 10:17:15 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	str_to_num(char *ptr)
{
	int	i;
	int	num;	

	num = 0;
	i = 0;
	while (ptr[i] >= 48 && ptr[i] <= 57)
	{
		num *= 10;
		num += ptr[i] - 48;
		i++;
	}
	return (num);
}

int ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	num;

	sign = 0;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = !sign;
		i++;
	}
	num = str_to_num((char *)nptr + i);
	if (sign)
		num *= -1;
	return (num);
}

/*
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: ./a.out \"mystring\"\n");
		return (1);
	}
	printf("ft_atoi gives %i\n", ft_atoi(argv[1]));
	printf("atoi gives %i\n", atoi(argv[1]));
	printf("\nChecking tabs, should print 256, ft_atoi result: %i\n", ft_atoi("\t\n\v\f\r +256"));
	printf("\nChecking tabs, should print 256, atoi result: %i\n", ft_atoi("\t\n\v\f\r +256"));
	//printf("%i\n", ft_atoi("	   ++---00-02hgg"));
	//printf("%i\n", ft_atoi("     ++---hgg"));
	//printf("%i\n", ft_atoi("    ---++--929292hgg"));
	return (0);
}
*/