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
	int		num_cmds;
	int		**pipes;
	t_cmd	*cmds;
	pid_t	pid;

	num_cmds = get_num_cmds(argc, argv);
	pipes = create_pipes(num_cmds - 1); 
	cmds = create_arrays(argv, envp, pipes, num_cmds);
	if (!cmds)
		cmds_array_error(pipes, num_cmds);
	pid = fork();
	if (pid == -1)
		fork_error(argc, pipes, cmds);
	if (pid == 0)
		first_child(argc, argv, pipes, cmds);
	cmds[0].pid = pid; 
	bonus_loop(argc, pipes, cmds);
	pid = fork();
	if (pid == -1)
		fork_error(argc, pipes, cmds);
	if (pid == 0)
		last_child(argv[argc - 1], pipes, cmds, num_cmds);
	cmds[num_cmds - 1].pid = pid;
	wait_cleanup(argc, pipes, cmds, num_cmds);
	return (0);
}

void	bonus_loop(int ac, int **pipes, t_cmd *cmds)
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
		cmds[pipe_num].pid = pid;
	}
	return ;
}

int	get_num_cmds(int ac, char **av)
{
	if (ac > 4)
	{
		if (ft_strncmp(av[1], "here_doc", 8) == 0)
			return (ac - 4);
		return (ac - 3);
	}
	ft_printf("Invalid number of arguments\n");
	exit(EXIT_FAILURE);
}
