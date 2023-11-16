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

void	wait_cleanup(int **pipes, t_cmd *cmds, int num_cmds)
{
	close_pipes(0, num_cmds - 1, pipes);
	while (wait(NULL) > 0);
	free_arrays(cmds, num_cmds);
	free_pipes(pipes, num_cmds - 1);
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
/*
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
*/
void	free_arrays(t_cmd *cmds, int num_cmds)
{
	int	i;
	int	j;

	i = -1;
	while (++i < num_cmds)
	{
		if (cmds[i].adr)
			free(cmds[i].adr);
		if (!cmds[i].args)
			continue ;
		j = 0;
		while (cmds[i].args[j])
			free(cmds[i].args[j++]);
		free(cmds[i].args);
	}
	free(cmds);
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
