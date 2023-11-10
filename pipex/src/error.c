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

void	fork_error(int ac, int **pipes, char ***cmds) //also needs to wait ... and to free pids, of course
{
	close_pipes(0, ac - 4, pipes);
	free_arrays(cmds, ac);
	free_pipes(pipes, ac); 
	perror("Fork: ");
	exit(EXIT_FAILURE);
}

void	file_error(char *name, int fd)
{
	ft_printf("%s: %s\n", strerror(errno), name);
	close(fd);
	exit(EXIT_FAILURE);
}

void	print_cmd_error(char **cmd)
{	
	if (!cmd[0])
	{
		write(2, "Command not found: ", 19);
		write(2, cmd[1], ft_strlen(cmd[1]));
		write(2, "\n", 1);
	}
	else
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, ": ", 2);
		write(2, cmd[1], ft_strlen(cmd[1]));
		write(2, "\n", 1);
	}
	return ;
}
