/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 12:50:51 by eusatiko          #+#    #+#             */
/*   Updated: 2022/12/29 12:55:01 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(int n)
{
	int	len;

	if (n > 0)
		len = 0;
	else
		len = 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;

	i = get_len(n);
	str = malloc(i + 1);
	if (str == NULL)
		return (NULL);
	if (n == 0)
		str[0] = 48;
	str[i--] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		str[i--] = 48 - (n % 10);
		n = n / 10 * -1;
	}
	while (n != 0)
	{
		str[i--] = 48 + (n % 10);
		n /= 10;
	}
	return (str);
}

/*
#include <stdio.h>
#include <string.h>

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	int n = atoi(argv[1]);
	printf("number is %i\n", n);
	char *str = ft_itoa(n);
	printf("str is %s\n", str);
	free(str);
	return (0);
}
*/
