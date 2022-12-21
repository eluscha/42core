/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:44:47 by eusatiko          #+#    #+#             */
/*   Updated: 2022/12/10 14:17:39 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strjoin(char const *s1, char const *s2)
{
	char	*strcat;
	size_t	len1;
	size_t	len2;
	size_t	i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2); 
	strcat = malloc(len1 + len2 + 1);
	if (strcat == NULL)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		strcat[i] = s1[i];
		i++;
	}
	while (i < len1 + len2 + 1)
	{
		strcat[i] = s2[i - len1];
		i++;
	}
	return (strcat);
}

/*
#include <stdio.h>
int main(int argc, char **argv)
{
	if (argc != 3)
		return (1);
	char *str = ft_strjoin(argv[1], argv[2]);
	printf("%s\n", str);
	char *str2 = ft_strjoin(argv[0], str);
	printf("%s\n", str2);
	free(str);
	free(str2);
	return (0);
}
*/