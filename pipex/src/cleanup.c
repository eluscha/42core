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

void	free_arrays(char ***cmds, int len)
{
	int	i;
	int	j;

	i = -1;
	while (++i < len)
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

void	free_pipes(int **pipes, int argc)
{
	int	i;

	i = 0;
	while (i < argc - 4)
	{
		if (!pipes[i])
			break ;
		else
			free(pipes[i++]);
	}
	free(pipes);
}

void	close_pipes(int start, int end, int **pipes)
{
	int	i;

	i = start;
	while (++i < end)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
}
