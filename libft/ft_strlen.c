/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 11:10:49 by eusatiko          #+#    #+#             */
/*   Updated: 2022/12/05 11:46:59 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*((char *)s + i) != '\0')
		i++;
	return (i);
}

#include <stdio.h>
int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	printf("%i\n", ft_strlen(argv[1]));
	return (0);
}
