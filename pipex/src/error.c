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
	perror("Fork");
	close_pipes(pipes, 0, num_pipes);
	while (wait(NULL) > 0);
	free_pipes(pipes, num_pipes); 
	exit(errno);
}

void	file_error(char *fname, t_cmd *cmd, int **pipes, int num_pipes)
{
	close_pipes(pipes, 0, num_pipes);
	free_pipes(pipes, num_pipes);
	if (fname)
	{
		perror(fname);
		free_cmd(cmd);
	}
	else
		perror("Failed to write temp");
	free(cmd);
	//ft_putstr_fd(ft_itoa(errno), 2); //
	exit(errno);
}

void	fill_cmd_error(t_cmd *cmd, int **pipes, int num_pipes)
{
	ft_putstr_fd("Failed to fill_cmd!", 2);
	free_cmd(cmd);
	free(cmd);
	free_pipes(pipes, num_pipes);
	exit(EXIT_FAILURE);
}

void	print_cmd_error(t_cmd *cmd)
{	
	if (ft_strncmp(cmd->adr, "none", 4) == 0)
	{
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": Command not found\n", 2);
	}
	else
		perror(cmd->args[0]);
	return ;
}
