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

void	check_init_error(t_cmd *cmd, int *onepipe)
{
	if (cmd)
		return ;
	close(onepipe[0]);
	close(onepipe[1]);
	exit(EXIT_FAILURE);
}

void	check_fork_error(pid_t pid, int *onepipe)
{
	if (pid != -1)
		return ;
	close(onepipe[0]);
	close(onepipe[1]);
	while (wait(NULL) != -1)
		continue ;
	exit(EXIT_FAILURE);
}

void	file_error(char *fname, t_cmd *cmd, int *onepipe)
{
	perror(fname);
	close(onepipe[0]);
	close(onepipe[1]);
	free(cmd);
	exit(EXIT_FAILURE);
}

void	fill_cmd_error(t_cmd *cmd)
{
	ft_putstr_fd("Failed to fill_cmd!", 2);
	free_cmd(cmd);
	free(cmd);
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
