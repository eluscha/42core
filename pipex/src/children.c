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

void	bonus_loop(int **pipes, t_cmd *cmd, int num_pipes)
{
	int		cnum;
	int		pid;

	cnum = 0;
	while (++cnum < num_pipes)
	{
		pid = fork();
		check_fork_error(pid, pipes, num_pipes);
		if (pid == 0)
			mid_child(cmd, cnum, pipes, num_pipes);
	}
	return ;
}

void	first_child(t_cmd *cmd, int **pipes, int num_pipes)
{
	int	fd_file1;
	char	*fname;

	if (cmd->here_doc)
		fname = "temp";
	else
		fname = cmd->av[1];
	close_pipes(pipes, 1, num_pipes);
	close(pipes[0][0]);
	fd_file1 = open(fname, O_RDONLY);
	if (fd_file1 == -1)
		file_error(fname, cmd, pipes[0][1]);
	dup2(fd_file1, 0);
	dup2(pipes[0][1], 1);
	close(fd_file1);
	close(pipes[0][1]);
	if (!fill_cmd(cmd, 0, cmd->here_doc))
		fill_cmd_error(cmd); //does it need to free pipes ?
	execve(cmd->adr, cmd->args, 0);
	free_cmd(cmd);
	free(cmd); //do i also need to free pipes ???
	exit(errno);
}

void	mid_child(t_cmd *cmd, int cnum, int **pipes, int num_pipes)
{
	
	close_pipes(pipes, 0, cnum - 1);
	close_pipes(pipes, cnum + 1, num_pipes);
	close(pipes[cnum - 1][1]);
	close(pipes[cnum][0]);
	dup2(pipes[cnum - 1][0], 0);
	dup2(pipes[cnum][1], 1);
	close(pipes[cnum - 1][0]);
	close(pipes[cnum][1]);
	if (!fill_cmd(cmd, cnum, cmd->here_doc))
		fill_cmd_error(cmd); //does it need to free pipes ?
	execve(cmd->adr, cmd->args, 0);
	//print_cmd_error(cmd);
	free_cmd(cmd);
	free(cmd); //free pipes?
	exit(errno);
}

void	last_child(char *fname, t_cmd *cmd, int **pipes, int num_pipes)
{
	int	fd_file2;

	close_pipes(pipes, 0, num_pipes - 1);
	close(pipes[num_pipes - 1][1]);
	if (cmd->here_doc)
		fd_file2 = open(fname, O_APPEND | O_WRONLY | O_CREAT, 0777);
	else
		fd_file2 = open(fname, O_TRUNC | O_WRONLY | O_CREAT, 0777);
	if (fd_file2 == -1)
		file_error(fname, cmd, pipes[num_pipes - 1][0]);
	dup2(pipes[num_pipes - 1][0], 0);
	dup2(fd_file2, 1);
	close(fd_file2);
	close(pipes[num_pipes - 1][0]);
	if (!fill_cmd(cmd, num_pipes, cmd->here_doc))
		fill_cmd_error(cmd); //will exit_failure //does it need to free pipes ?
	execve(cmd->adr, cmd->args, 0);
	free_cmd(cmd);
	free(cmd); //free pipes ?
	exit(errno);
}
