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

void	first_child(t_cmd *cmd, int *onepipe)
{
	int		fd_file1;
	char	*fname;
	int		status;

	fname = cmd->av[1];
	fd_file1 = open(fname, O_RDONLY);
	if (fd_file1 == -1)
		file_error(fname, cmd, onepipe);
	close(onepipe[0]);
	dup2(fd_file1, 0);
	dup2(onepipe[1], 1);
	close(fd_file1);
	close(onepipe[1]);
	if (!fill_cmd(cmd, 0))
		fill_cmd_error(cmd);
	execve(cmd->adr, cmd->args, cmd->envp);
	status = print_cmd_error(cmd);
	free_cmd(cmd);
	free(cmd);
	exit(status);
}

void	last_child(t_cmd *cmd, int *onepipe)
{
	int		fd_file2;
	char	*fname;
	int		status;

	fname = cmd->av[4];
	fd_file2 = open(fname, O_TRUNC | O_WRONLY | O_CREAT, 0777);
	if (fd_file2 == -1)
		file_error(fname, cmd, onepipe);
	close(onepipe[1]);
	dup2(onepipe[0], 0);
	dup2(fd_file2, 1);
	close(fd_file2);
	close(onepipe[0]);
	if (!fill_cmd(cmd, 1))
		fill_cmd_error(cmd);
	execve(cmd->adr, cmd->args, cmd->envp);
	status = print_cmd_error(cmd);
	free_cmd(cmd);
	free(cmd);
	exit(status);
}
