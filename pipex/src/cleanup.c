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

void	wait_cleanup(int ac, int **pipes, char ***cmds, pid_t *pids)
{
	close_pipes(0, ac - 4, pipes);
	wait_for_all(pids, ac - 3);
	free_arrays(cmds, ac);
	free_pipes(pipes, ac);
	free(pids);
	return ;
}

void	close_pipes(int start, int end, int **pipes)
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

void	wait_for_all(pid_t *pids, int len)
{
	int	i;
	int	status;

	i = 0;
	while (i < len)
	{
		waitpid(pids[i], &status, 0);
		//if (status != 0)
		//	check_cmd_errors(cmds[i]);
		i++;
	}
	return ;
}

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
