/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:50:42 by eusatiko          #+#    #+#             */
/*   Updated: 2023/10/30 14:50:57 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(int ac, char **av, int **pipes, char ***cmds)
{
	int		fd_file1;

	close_pipes(1, ac - 4, pipes);
	close(pipes[0][0]);
	fd_file1 = open(av[1], O_RDONLY);
	if (fd_file1 == -1)
		file_error(av[1], pipes[0][1]);
	check_cmd_errors(cmds[0], fd_file1, pipes[0][1], 0);
	dup2(fd_file1, 0);
	dup2(pipes[0][1], 1);
	close(fd_file1);
	close(pipes[0][1]);
	execve(cmds[0][0], &cmds[0][1], 0);
	perror("execve error: ");
	exit(EXIT_FAILURE);
}

void	mid_child(int pnum, int ac, int **pipes, char ***cmds)
{
	close_pipes(0, pnum - 1, pipes);
	close_pipes(pnum + 1, ac - 4, pipes);
	close(pipes[pnum - 1][1]);
	close(pipes[pnum][0]);
	check_cmd_errors(cmds[pnum], pipes[pnum - 1][0], pipes[pnum][0], pnum);
	dup2(pipes[pnum - 1][0], 0);
	dup2(pipes[pnum][1], 1);
	close(pipes[pnum - 1][0]);
	close(pipes[pnum][1]);
	execve(cmds[pnum][0], &cmds[pnum][1], 0);
	perror("execve error: ");
	exit(EXIT_FAILURE);
}

void	last_child(int ac, char **av, int **pipes, char ***cmds)
{
	int		fd_file2;

	close_pipes(0, ac - 5, pipes);
	close(pipes[ac - 5][1]);
	fd_file2 = open(av[ac - 1], O_TRUNC | O_WRONLY | O_CREAT, 0777);
	if (fd_file2 == -1)
		file_error(av[ac - 1], pipes[ac - 5][0]);
	check_cmd_errors(cmds[ac - 4], fd_file2, pipes[ac - 5][0], ac - 4);
	dup2(pipes[ac - 5][0], 0);
	dup2(fd_file2, 1);
	close(fd_file2);
	close(pipes[ac - 5][0]);
	execve(cmds[ac - 4][0], &cmds[ac - 4][1], 0);
	perror("execve error: ");
	exit(EXIT_FAILURE);
}
