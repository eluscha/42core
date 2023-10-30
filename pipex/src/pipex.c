/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:13:38 by eusatiko          #+#    #+#             */
/*   Updated: 2023/10/16 12:13:46 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		**pipes;
	char	***cmds;
	int		pipe_num;
	int		pid;

	check_argc(argc);
	pipes = create_pipes(argc);
	cmds =  create_arrays(argc, argv, envp);
	if (!cmds)
	{
		free_pipes(pipes, argc);
		exit(1);
	}
	pid = fork();
	if (pid == -1)
		fork_error(argc, pipes, cmds);
	if (pid == 0)
		first_child(argc, argv, pipes, cmds);
	pipe_num = 1;
	while (pipe_num < argc - 4)
	{
		pid = fork();
		if (pid == -1)
			fork_error(argc, pipes, cmds);
		if (pid == 0)
			mid_child(pipe_num, argc, pipes, cmds);
		pipe_num++;
	}
	pid = fork();
	if (pid == -1)
		fork_error(argc, pipes, cmds);
	if (pid == 0)
		last_child(argc, argv, pipes, cmds);
	close_pipes(-1, argc - 4, pipes);
	free_arrays(cmds, argc - 3);
	free_pipes(pipes, argc); 
	if (wait(NULL) != -1 || errno != ECHILD)
		return (-1);
	return (0);
}
