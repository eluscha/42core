/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:43:08 by eusatiko          #+#    #+#             */
/*   Updated: 2023/02/06 15:03:31 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

char	*get_next_line(int fd, int error)
{
	static char	*static_bf;	//has to keep the value between function calls, a pointer to heap
	char	*line;	//line value is new for every function call
	
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (NULL);
	static_bf = ft_fill_bf(fd, static_bf, error); //read from remainder (if present) and file (using calloc (malloc), free)
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

char	*ft_fill_bf(int fd, char *static_bf, int error)
{
	char	*temp_bf;
	int		bytes_read;
	
	//printf("we are in ft_fill_bf\n");
	
	//if static_bf was not initialized yet - the value will always be NULL ?
	if (!static_bf)
	{
		printf("we will now initialize static_bf\n");
		static_bf = ft_calloc(1, sizeof(char)); //empty string
	}
	temp_bf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	//protect here ?
	bytes_read = 1; //any value bigger than 0
	while (bytes_read > 0)	//while we read over 0 bytes and did not find '\n'
	{
		if (error)
			bytes_read = -1;
		else 
			bytes_read = read(fd, temp_bf, BUFFER_SIZE);
		printf("bytes_read is %i\n", bytes_read);
		if (bytes_read == 0 || bytes_read == -1)
		{
			free(temp_bf);
			if (bytes_read == 0)
				return (static_bf);
			printf("we will now free static_bf and set it to NULL\n");
			free(static_bf);
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
