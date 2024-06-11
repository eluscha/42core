/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 12:42:38 by eusatiko          #+#    #+#             */
/*   Updated: 2022/12/29 12:42:47 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	if (s == NULL)
		return (NULL);
	str = malloc(ft_strlen(s) + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*
char	example_f(unsigned int i, char c)
{
	return (c - i);
}

#include <stdio.h>
int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	char	*str = ft_strmapi(argv[1], example_f);
	printf("The resulting string is %s\n", str);
	free(str);
	return (0);
}
*/
