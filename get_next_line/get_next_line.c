/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:43:08 by eusatiko          #+#    #+#             */
/*   Updated: 2023/02/09 11:49:28 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	*static_bf;	//has to keep the value between function calls, a pointer to heap
	char	*line;	//line value is new for every function call
	
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (static_bf)
			free(static_bf);
		static_bf = NULL;
		return (NULL);
	}
	static_bf = ft_fill_bf(fd, static_bf); //read from remainder (if present) and file (using malloc, free)
	if (!static_bf)
		return (NULL);
	line = ft_save_line(&static_bf);	//line part (before \n)
	if (!line)
	{
		if (ft_strlen(static_bf) != 0)
			line = ft_strjoin(static_bf, "\0");
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
	if (!temp_bf)
	{
		if (static_bf)
			free(static_bf);
		return (NULL);
	}
	bytes_read = 1; //any value bigger than 0
	while (bytes_read > 0)	//while we read over 0 bytes and did not find '\n'
	{
		bytes_read = read(fd, temp_bf, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(static_bf);
			static_bf = NULL;
		}
		if (bytes_read == 0 || bytes_read == -1)
			break;
		temp_bf[bytes_read] = '\0'; // null-terminate the string in the temporary buffer
		static_bf = ft_join(static_bf, temp_bf);	// join remainder with what sits in temp_bf
		if (ft_strchr(temp_bf, '\n'))	//reached end line already, should stop reading now
			break ;
	}
	free(temp_bf);
	return (static_bf);
}

char	*ft_join(char *static_bf, char *temp_bf)
{
	char	*joined;
	
	//printf("we are in ft_join\n");
	if (!static_bf)
		static_bf = ft_strdup("");
	joined = ft_strjoin(static_bf, temp_bf); //joined string sits on the heap
	free(static_bf); //old value not relevant anymore
	//printf("joined str is %s\n", joined);
	return (joined); //static ptr value updated to the new string
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
			break;
		i++;
	}
	//printf("i is %i and len is ft_strlen(*static_adr) is %i\n", i, ft_strlen(*static_adr));
	line = NULL;
	if (i != (int)ft_strlen(*static_adr))
		line = malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	ft_strlcpy(line, *static_adr, i + 2);
	remainder = ft_strdup(*(static_adr) + i + 1);
	free(*static_adr);
	*static_adr = remainder;
	return (line);
}
