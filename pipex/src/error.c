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

void	check_cmd_errors(char **cmd)
{
	if (!cmd[0])
		ft_printf("command not found: %s\n", cmd[1]);
	else if (cmd[0] == (char *)1)
		ft_printf("permission denied: %s\n", cmd[1]);
	return ;
}
