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
	pid_t	*pids;
	pid_t	pid;

	check_argc(argc);
	pipes = create_pipes(argc);
	cmds = create_arrays(argc, argv, envp, pipes);
	pids = create_pids(argc, pipes, cmds);
	pid = fork();
	if (pid == -1)
		fork_error(argc, pipes, cmds);
	if (pid == 0)
		first_child(argc, argv, pipes, cmds);
	pids[0] = pid; 
	bonus_loop(argc, pipes, cmds, pids);
	pid = fork();
	if (pid == -1)
		fork_error(argc, pipes, cmds);
	if (pid == 0)
		last_child(argc, argv, pipes, cmds);
	pids[argc - 4] = pid;
	wait_cleanup(argc, pipes, cmds, pids);
	return (0);
}

void	bonus_loop(int ac, int **pipes, char ***cmds, pid_t *pids)
{
	int		pipe_num;
	int		pid;

	pipe_num = 0;
	while (++pipe_num < ac - 4)
	{
		pid = fork();
		if (pid == -1)
			fork_error(ac, pipes, cmds);
		if (pid == 0)
			mid_child(pipe_num, ac, pipes, cmds);
		pids[pipe_num] = pid;
	}
	return ;
}

void	check_argc(int ac)
{
	if (ac > 4)
		return ;
	ft_printf("Invalid number of arguments\n");
	exit(EXIT_FAILURE);
}
