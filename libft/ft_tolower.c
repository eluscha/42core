/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:01:05 by eusatiko          #+#    #+#             */
/*   Updated: 2022/12/07 13:02:15 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	return (c);
}

/*
#include <stdio.h>
#include <ctype.h>
int main(int argc, char** argv)
{
	if (argc != 2)
		return (1);
	printf("tolower %c\n", tolower(argv[1][0]));
	printf("ft_tolower %c\n", ft_tolower(argv[1][0]));
}
*/