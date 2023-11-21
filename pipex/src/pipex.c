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
	int		here_doc;
	int		num_pipes;
	int		**pipes;
	t_cmd	*cmd;
	pid_t	pid;

	num_pipes = get_num_pipes(argc, argv, &here_doc);
	pipes = create_pipes(num_pipes);
	cmd = init_struct(argv, envp, here_doc);
	check_init_error(cmd, pipes, num_pipes);
	if (here_doc)
		write_tmp_file(cmd);
	pid = fork();
	check_fork_error(pid, pipes, num_pipes);
	if (pid == 0)
		first_child(cmd, pipes, num_pipes);
	bonus_loop(pipes, cmd, num_pipes);
	pid = fork();
	check_fork_error(pid, pipes, num_pipes);
	if (pid == 0)
		last_child(argv[argc - 1], cmd, pipes, num_pipes);
	close_pipes(pipes, 0, num_pipes);
	while (wait(NULL) != -1);
	free_pipes(pipes, num_pipes);
	if (here_doc)
		unlink("temp");
	free(cmd); // also certainly need in early exits !
	exit(EXIT_SUCCESS);
}

int	get_num_pipes(int ac, char **av, int *here_doc)
{
	if (ac > 4)
	{
		if (ft_strncmp(av[1], "here_doc", 8) == 0)
		{
			*here_doc = 1;
			return (ac - 5);
		}
		*here_doc = 0;
		return (ac - 4);
	}
	ft_printf("Invalid number of arguments\n");
	exit(EXIT_FAILURE);
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

void	close_pipes(int **pipes, int start, int end)
{
	int	i;

	i = start;
	while (i < end)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	return ;
}

void	free_pipes(int **pipes, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (!pipes[i])
			break ;
		else
			free(pipes[i++]);
	}
	free(pipes);
}