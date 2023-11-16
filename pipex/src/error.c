/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:34:16 by eusatiko          #+#    #+#             */
/*   Updated: 2023/10/30 15:34:20 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipe_error(int **pipes, int i)
{
	ft_printf("Pipe index %d: %s\n", i, strerror(errno));
	if (pipes[i])
		free(pipes[i]);
	close_pipes(0, i, pipes);
	while (--i >= 0)
		free(pipes[i]);
	exit(EXIT_FAILURE);
}

void	check_array_error(t_cmd *cmds, int **pipes, int num_cmds)
{
	if (cmds)
		return ;
	write(2, "Failed to ft_calloc cmds array\n", 31);
	close_pipes(0, num_cmds - 1, pipes);
	free_pipes(pipes, num_cmds - 1);
	exit(EXIT_FAILURE);
}

void	fork_error(int **pipes, t_cmd *cmds, int num_cmds) //also needs to wait ... and to free pids, of course
{
	close_pipes(0, num_cmds - 1, pipes);
	free_arrays(cmds, num_cmds);
	free_pipes(pipes, num_cmds - 1); 
	perror("Fork: ");
	exit(EXIT_FAILURE);
}

void	file_error(char *name, int fd)
{
	ft_printf("%s: %s\n", strerror(errno), name);
	close(fd);
	exit(EXIT_FAILURE);
}

void	print_cmd_error(t_cmd *cptr)
{	
	if (!cptr->adr)
	{
		write(2, "Command not found: ", 19);
		write(2, cptr->args[0], ft_strlen(cptr->args[0]));
		write(2, "\n", 1);
	}
	else
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, ": ", 2);
		write(2, cptr->args[0], ft_strlen(cptr->args[0]));
		write(2, "\n", 1);
	}
	return ;
}
