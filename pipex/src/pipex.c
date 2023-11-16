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
	cmds = create_array(argc, argv, envp, num_cmds);
	check_array_error(cmds, pipes, num_cmds);
	pid = fork();
	if (pid == -1)
		fork_error(pipes, cmds, num_cmds);
	if (pid == 0)
		first_child(argv, pipes, cmds, num_cmds);
	cmds[0].pid = pid; 
	bonus_loop(pipes, cmds, num_cmds);
	pid = fork();
	if (pid == -1)
		fork_error(pipes, cmds, num_cmds);
	if (pid == 0)
		last_child(argv[argc - 1], pipes, cmds, num_cmds);
	cmds[num_cmds - 1].pid = pid;
	wait_cleanup(pipes, cmds, num_cmds);
	return (0);
}

int	**create_pipes(int num)
{
	int	**pipes;
	int	i;

	pipes = ft_calloc(num, sizeof(int *));
	if (!pipes)
	{
		ft_printf("failed ft_calloc\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < num)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			pipe_error(pipes, i);
		if (pipe(pipes[i]) == -1)
			pipe_error(pipes, i);
		i++;
	}
	return (pipes);
}

void	bonus_loop(int **pipes, t_cmd *cmds, int num_cmds)
{
	int		cnum;
	int		pid;

	cnum = 0;
	while (++cnum < num_cmds - 1)
	{
		pid = fork();
		if (pid == -1)
			fork_error(pipes, cmds, num_cmds);
		if (pid == 0)
			mid_child(cnum, pipes, cmds, num_cmds);
		cmds[cnum].pid = pid;
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
