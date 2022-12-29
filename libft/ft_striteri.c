/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:02:46 by eusatiko          #+#    #+#             */
/*   Updated: 2022/12/29 13:02:58 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (s == NULL)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
	return ;
}

/*
void	example_f(unsigned int i, char *p_c)
{
	*p_c -= i;
}

#include <stdio.h>
int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	ft_striteri(argv[1], example_f);
	printf("argv[1] is now: %s\n", argv[1]);
	return (0);
}
*/
