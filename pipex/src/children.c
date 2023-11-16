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

void	first_child(char **av, int **pipes, t_cmd *cmds, int num_cmds)
{
	int		fd_file1;

	close_pipes(1, num_cmds - 1, pipes);
	close(pipes[0][0]);
	fd_file1 = open(av[1], O_RDONLY);
	if (fd_file1 == -1)
		file_error(av[1], pipes[0][1]);
	dup2(fd_file1, 0);
	dup2(pipes[0][1], 1);
	close(fd_file1);
	close(pipes[0][1]);
	if (!fill_cmd(cmds, 0))
		exit(EXIT_FAILURE);
	execve(cmds[0].adr, cmds[0].args, 0);
	print_cmd_error(&cmds[0]);
	exit(EXIT_FAILURE);
}

void	mid_child(int cnum, int **pipes, t_cmd *cmds, int num_cmds)
{
	close_pipes(0, cnum - 1, pipes);
	close_pipes(cnum + 1, num_cmds - 1, pipes);
	close(pipes[cnum - 1][1]);
	close(pipes[cnum][0]);
	dup2(pipes[cnum - 1][0], 0);
	dup2(pipes[cnum][1], 1);
	close(pipes[cnum - 1][0]);
	close(pipes[cnum][1]);
	if (!fill_cmd(cmds, cnum))
		exit(EXIT_FAILURE);
	execve(cmds[cnum].adr, cmds[cnum].args, 0);
	print_cmd_error(&cmds[cnum]);
	exit(EXIT_FAILURE);
}

void	last_child(char *fname, int **pipes, t_cmd *cmds, int num_cmds)
{
	int		fd_file2;
	int		rpnum;

	rpnum = num_cmds - 2;
	close_pipes(0, rpnum, pipes);
	close(pipes[rpnum][1]);
	fd_file2 = open(fname, O_TRUNC | O_WRONLY | O_CREAT, 0777);
	if (fd_file2 == -1)
		file_error(fname, pipes[rpnum][0]);
	dup2(pipes[rpnum][0], 0);
	dup2(fd_file2, 1);
	close(fd_file2);
	close(pipes[rpnum][0]);
	if (!fill_cmd(cmds, num_cmds - 1))
		exit(EXIT_FAILURE);
	execve(cmds[num_cmds - 1].adr, cmds[num_cmds - 1].args, 0);
	print_cmd_error(&cmds[num_cmds - 1]);
	exit(EXIT_FAILURE);
}
