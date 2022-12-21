/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 14:18:31 by eusatiko          #+#    #+#             */
/*   Updated: 2022/12/11 10:50:16 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	inset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	count_trims(char const *s1, char const *set, size_t *left)
{
	size_t	finallen;
	size_t	i;
	size_t	right;

	finallen = ft_strlen(s1);
	i = 0;
	right = 0;
	while (s1[i] != '\0')
	{
		if (inset(s1[i], set))
			(*left)++;
		else
			break ;
		i++;
	}
	i = finallen - 1;
	while (i >= *left)
	{		
		if (inset(s1[i], set))
			right++;
		else
			break ;
		i--;
	}
	return (finallen - (*left + right));
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	i;
	size_t	finallen;
	char	*ptr;

	start = 0;
	i = 0;
	finallen = count_trims(s1, set, &start);
	ptr = malloc(finallen + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < finallen)
	{
		ptr[i] = s1[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	if (argc != 3)
		return (1);
	char	*str = ft_strtrim(argv[1], argv[2]);
	printf("%s\n", str);
	free(str);
	return (0);
}
*/