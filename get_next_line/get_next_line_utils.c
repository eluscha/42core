/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:48:16 by eusatiko          #+#    #+#             */
/*   Updated: 2023/01/25 14:36:04 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if ((char)c == 0)
		return ((char *)s + i);
	return (NULL);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		while (src[i] != '\0')
			i++;
		return (i);
	}
	while (src[i] != '\0')
	{
		if (i < size - 1)
			dst[i] = src[i];
		i++;
	}
	if (i < size - 1)
		dst[i] = src[i];
	else
		dst[size - 1] = '\0';
	return (i);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*((char *)s + i) != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
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

char	*ft_strdup(const char *s)
{
	char		*ptr;
	size_t		i;
	size_t		len;

	len = ft_strlen(s);
	ptr = malloc(len + 1);
	if (ptr == 0)
		return (0);
	i = 0;
	while (i < len + 1)
	{
		ptr[i] = s[i];
		i++;
	}
	return (ptr);
}
