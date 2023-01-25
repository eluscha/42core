/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:43:08 by eusatiko          #+#    #+#             */
/*   Updated: 2023/01/25 14:36:30 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	*static_bf;	//has to keep the value between function calls, a pointer to heap
	char	*line;	//line value is new for every function call
	
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (NULL);
	static_bf = ft_fill_bf(fd, static_bf); //read from remainder (if present) and file (using calloc (malloc), free)
	if (!static_bf)
		return (NULL);
	line = ft_save_line(&static_bf);	//line part (before \n)
	return (line);
}

char	*ft_fill_bf(int fd, char *static_bf)
{
	char	*temp_bf;
	int		bytes_read;
	
	//printf("we are in ft_fill_bf\n");
	
	//if static_bf was not initialized yet - the value will always be NULL ?
	if (!static_bf)
		static_bf = ft_calloc(1, sizeof(char)); //empty string
	temp_bf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes_read = 1; //any value bigger than 0
	while (bytes_read > 0)	//while we read over 0 bytes and did not find '\n'
	{
		bytes_read = read(fd, temp_bf, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(temp_bf);
			return (NULL);
		}
		temp_bf[bytes_read] = '\0'; // null-terminate the string in the temporary buffer
		//printf("temp_bf is %s\n", temp_bf);
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

	joined = ft_strjoin(static_bf, temp_bf); //joined string sits on the heap
	if (!joined)
		return NULL;
	free(static_bf); //old value not relevant anymore
	//printf("joined str is %s\n", joined);
	return (joined); //static ptr value updated to the new string
}

char	*ft_save_line(char **static_adr)
{
	int		len;
	int		i;
	char	*line;
	char	*remainder;

	//printf("we are in ft_save_line\n");
	//printf("*static_adr is %s\n", *static_adr);

	len = 0;
	i = 0;
	while (*(*static_adr + i) != '\0' && i < 10) 
	{
		//printf("char is %c\n", **static_adr);
		if (*(*static_adr + i) == '\n') // || *(*static_adr + i) == EOF ? 
		{
			len = i + 1;
			break ;
		}
		i++;
	}
	//printf("len is %i\n", len);
	if (!len)
		line = NULL;
	else
		line = malloc((len + 1) * sizeof(char));
	if (!line)
	{
		free(*static_adr);
		return (NULL);
	}
	ft_strlcpy(line, *static_adr, len + 1);
	//printf("line is (%s)\n", line);
	remainder = ft_strdup(*(static_adr) + len);
	free(*static_adr);
	*static_adr = remainder;
	return (line);
}