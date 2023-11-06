/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:00:18 by eusatiko          #+#    #+#             */
/*   Updated: 2023/10/30 15:00:28 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_arrays(char ***cmds, int ac)
{
	int	i;
	int	j;

	i = -1;
	while (++i < ac - 3)
	{
		if (!cmds[i])
			continue ;
		if (cmds[i][0])
			free(cmds[i][0]);
		j = 1;
		while (cmds[i][j])
			free(cmds[i][j++]);
		free(cmds[i]);
	}
	free(cmds);
	return ;
}

void	free_pipes(int **pipes, int ac)
{
	int	i;

	i = 0;
	while (i < ac - 4)
	{
		if (!pipes[i])
			break ;
		else
			free(pipes[i++]);
	}
	free(pipes);
}

void	close_pipes(int end, int **pipes)
{
	int	i;

	i = -1;
	while (++i < end)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
}

void	cleanup(int ac, int **pipes, char ***cmds)
{
	free_arrays(cmds, ac);
	free_pipes(pipes, ac);
	return ;
}
