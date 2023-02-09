/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:43:08 by eusatiko          #+#    #+#             */
/*   Updated: 2023/02/09 14:55:11 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	char		*line;
	static char	*static_bf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	static_bf = ft_fill_bf(fd, static_bf);
	if (!static_bf)
		return (NULL);
	line = ft_save_line(&static_bf);
	if (!line)
	{
		if (ft_strlen(static_bf) != 0)
		{
			line = ft_strjoin(static_bf, "\0");
			printf("used malloc in get_next line\n");
		}
		free(static_bf);
		static_bf = NULL;
	}
	return (line);
}

char	*ft_fill_bf(int fd, char *static_bf)
{
	char	*temp_bf;
	int		bytes_read;

	temp_bf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	printf("used malloc to allocat temp_bf\n");
	if (!temp_bf)
	{
		free(static_bf);
		return (NULL);
	}
	temp_bf[0] = '\0';
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(temp_bf, '\n'))
	{
		bytes_read = read(fd, temp_bf, BUFFER_SIZE);
		printf("bytes_read is %i\n", bytes_read);
		if (bytes_read == -1)
		{
			free(static_bf);
			static_bf = NULL;
			break ;
		}
		static_bf = ft_join(static_bf, temp_bf, bytes_read);
	}
	free(temp_bf);
	return (static_bf);
}

char	*ft_join(char *static_bf, char *temp_bf, int bytes_read)
{
	char	*joined;

	if (!static_bf)	
	{
		static_bf = ft_strdup("");
		printf("used malloc in ft_join 1\n");
	}
	temp_bf[bytes_read] = '\0';
	joined = ft_strjoin(static_bf, temp_bf);
	printf("used malloc in ft_join 2\n");
	free(static_bf);
	return (joined);
}

char	*ft_save_line(char **static_adr)
{
	int		i;
	char	*line;
	char	*remainder;

	i = 0;
	while (*(*static_adr + i) != '\0')
	{
		if (*(*static_adr + i) == '\n')
			break ;
		i++;
	}
	line = NULL;
	if (i != (int)ft_strlen(*static_adr))
	{
		line = malloc((i + 2) * sizeof(char));
		printf("used malloc in save_line 1\n");
	}	
	if (!line)
		return (NULL);
	ft_strlcpy(line, *static_adr, i + 2);
	remainder = ft_strdup(*(static_adr) + i + 1);
	printf("used malloc in save_line 2\n");
	free(*static_adr);
	*static_adr = remainder;
	return (line);
}
