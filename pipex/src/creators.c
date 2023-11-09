/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creators.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:02:21 by eusatiko          #+#    #+#             */
/*   Updated: 2023/10/30 15:02:27 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	**create_pipes(int ac)
{
	int	**pipes;
	int	i;

	pipes = ft_calloc(ac - 4, sizeof(int *));
	if (!pipes)
	{
		ft_printf("failed ft_calloc\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < ac - 4)
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

char	***create_arrays(int ac, char **av, char **envp, int **pipes)
{
	char	***cmds;
	int		i;

	cmds = ft_calloc(ac - 3, sizeof(char **));
	if (!cmds)
	{
		ft_printf("failed to ft_calloc cmds array\n");
		close_pipes(0, ac - 4, pipes);
		free_pipes(pipes, ac);
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < ac - 3)
	{
		if (ft_strlen(av[2+i]) == 0)
			cmds[i] = fill_null_cmd();
		else
			cmds[i] = fill_cmd(av[2 + i], envp);
	}
	return (cmds);
}

pid_t	*create_pids(int ac, int **pipes, char ***cmds)
{
	pid_t	*pids;

	pids = malloc(sizeof(pid_t) * (ac - 3));
	if (!pids)
	{
		ft_printf("failed to malloc pids array\n");
		close_pipes(0, ac - 4, pipes);
		free_pipes(pipes, ac);
		free_arrays(cmds, ac);
		exit(EXIT_FAILURE);
	}
	return (pids);
}