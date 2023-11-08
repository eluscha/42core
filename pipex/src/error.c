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

void	fork_error(int ac, int **pipes, char ***cmds)
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

void	check_cmd_errors(char **cmd, int fd1, int fd2, int cnum)
{
	if (!cmd)
	{
		sleep(cnum);
		ft_printf("permission denied: \n");
		close(fd1);
		close(fd2);
		exit(EXIT_FAILURE);
	}
	if (!cmd[0])
	{
		sleep(cnum);
		ft_printf("command not found: %s\n", cmd[1]);
		close(fd1);
		close(fd2);
		exit(EXIT_FAILURE);
	}
	return ;
}
