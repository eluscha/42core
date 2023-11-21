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
	close_pipes(pipes, 0, i);
	while (--i >= 0)
		free(pipes[i]);
	exit(EXIT_FAILURE);
}

void	check_init_error(t_cmd *cmd, int **pipes, int num_pipes)
{
	if (cmd)
		return ;
	close_pipes(pipes, 0, num_pipes);
	free_pipes(pipes, num_pipes);
	exit(EXIT_FAILURE);
}

void	check_fork_error(pid_t pid, int **pipes, int num_pipes) 
{
	if (pid != -1)
		return ;
	perror("Fork: ");
	close_pipes(pipes, 0, num_pipes);
	while (wait(NULL) > 0);
	free_pipes(pipes, num_pipes); 
	exit(EXIT_FAILURE);
}

void	file_error(char *fname, t_cmd *cmd, int fd)
{
	perror(fname);
	close(fd);
	free_cmd(cmd);
	free(cmd); //free pipes ?
	exit(EXIT_FAILURE);
}

void	fill_cmd_error(t_cmd *cmd)
{
	ft_putstr_fd("Failed to fill_cmd!", 2);
	free_cmd(cmd);
	free(cmd); //free pipes ?
	exit(EXIT_FAILURE);
}

void	print_cmd_error(t_cmd *cmd)
{	
	if (ft_strncmp(cmd->adr, "none", 4) == 0)
	{
		write(2, "Command not found: ", 19);
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
		write(2, "\n", 1);
	}
	else
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, ": ", 2);
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
		write(2, "\n", 1);
	}
	return ;
}
