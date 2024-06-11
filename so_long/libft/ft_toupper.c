/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:52:01 by eusatiko          #+#    #+#             */
/*   Updated: 2022/12/29 13:04:08 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	return (c);
}

/*
#include <stdio.h>
#include <ctype.h>
int main(int argc, char** argv)
{
	if (argc != 2)
		return (1);
	printf("toupper %c\n", toupper(argv[1][0]));
	printf("ft_toupper %c\n", ft_toupper(argv[1][0]));
}
*/
