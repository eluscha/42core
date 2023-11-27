/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipes_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:47:05 by eusatiko          #+#    #+#             */
/*   Updated: 2023/11/27 11:47:09 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	get_num_pipes(int ac, char **av, int *here_doc)
{
	if (ac > 4)
	{
		if (ft_strncmp(av[1], "here_doc", 8) == 0)
		{
			*here_doc = 1;
			return (ac - 5);
		}
		*here_doc = 0;
		return (ac - 4);
	}
	ft_printf("Invalid number of arguments\n");
	exit(EXIT_FAILURE);
}

int	**create_pipes(int num)
{
	int	**pipes;
	int	i;

	pipes = ft_calloc(num, sizeof(int *));
	if (!pipes)
	{
		ft_printf("failed ft_calloc\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < num)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			pipe_error(pipes, i);
		if (pipe(pipes[i]) == -1)
			pipe_error(pipes, i);
		i++;
	}
	return (pipes);
}

void	pipe_error(int **pipes, int i)
{
	ft_printf("Pipe index %d: %s\n", i, strerror(errno));
	if (pipes[i])
		free(pipes[i]);
	close_pipes(pipes, 0, i);
	while (--i >= 0)
		free(pipes[i]);
	exit(EXIT_FAILURE);
}

void	close_pipes(int **pipes, int start, int end)
{
	int	i;

	i = start;
	while (i < end)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	return ;
}

void	free_pipes(int **pipes, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (!pipes[i])
			break ;
		else
			free(pipes[i++]);
	}
	free(pipes);
}
