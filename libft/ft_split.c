/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:51:43 by eusatiko          #+#    #+#             */
/*   Updated: 2022/12/29 13:53:34 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_count(const char *s, char c)
{
	int	i;
	int	in_word;
	int	count;

	count = 0;
	i = 0;
	in_word = 0;
	while (s[i] != '\0')
	{
		if (!in_word && s[i] != c)
		{
			count += 1;
			in_word = 1;
		}
		else if (in_word && s[i] == c)
			in_word = 0;
		i++;
	}
	return (count);
}

int	get_len_word(const char *s, char c, int j, int *start_idx)
{
	int	started;
	int	count;

	started = 0;
	count = 0;
	while (s[j] != '\0')
	{
		if (started && s[j] == c)
			break ;
		else if (!started && s[j] != c)
		{
			started = 1;
			*start_idx = j;
			count++;
		}
		else if (started && s[j] != c)
			count++;
		j++;
	}
	return (count);
}

void	write_word(char *tostring, const char *s, int len, int start_idx)
{
	int	i;

	i = 0;
	while (i < len)
	{
		tostring[i] = s[start_idx + i];
		i++;
	}
	tostring[i] = '\0';
}

void	free_all(char **array, int i)
{
	int	idx;

	idx = 0;
	while (idx < i)
	{
		free(array[idx]);
		idx++;
	}
	free(array);
	return ;
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		i;
	int		j;
	int		start_idx;
	int		word_len;

	array = malloc((get_count(s, c) + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	j = 0;
	i = 0;
	while (i < get_count(s, c))
	{
		word_len = get_len_word(s, c, j, &start_idx);
		array[i] = malloc(word_len + 1);
		if (array[i] == NULL)
		{
			free_all(array, i);
			return (NULL);
		}
		write_word(array[i++], s, word_len, start_idx);
		j = start_idx + word_len;
	}
	array[i] = NULL;
	return (array);
}

/*
#include <stdio.h>
int main(int argc, char **argv)
{
	if (argc != 3)
		return (1);
	int i = 0;
	char **array = ft_split(argv[1], argv[2][0]);
	while (array[i] != NULL)
	{
		printf("array[%i] is %s\n", i, array[i]);
		free(array[i]);
		i++;
	}
	if (array != NULL)
		free(array);
	return 0;
}
*/
