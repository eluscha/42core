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

void	first_child(int ac, char **av, int **pipes, char ***cmds)
{
	int		i;
	int		fd_file1;
	char	*env[1];

	env[0] = NULL;
	i = 0;
	while (++i < ac - 4)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
	close(pipes[0][0]);
	fd_file1 = open(av[1], O_RDONLY);
	if (fd_file1 == -1)
	{
		perror(av[1]);
		exit(1);
	}
	dup2(fd_file1, 0);
	dup2(pipes[0][1], 1);
	close(fd_file1);
	close(pipes[0][1]);
	if (execve(cmds[0][0], &cmds[0][1], env) == -1)
		perror(cmds[0][0]);
	exit(1);
}

void	mid_child(int pnum, int ac, int **pipes, char ***cmds)
{
	int		i;
	char	*env[1];

	env[0] = NULL;
	i = -1;
	while (++i < pnum - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
	i++;
	while (++i < ac - 4)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
	close(pipes[pnum - 1][1]);
	close(pipes[pnum][0]);
	dup2(pipes[pnum - 1][0], 0);
	dup2(pipes[pnum][1], 1);
	close(pipes[pnum][0]);
	close(pipes[pnum][1]);
	if (execve(cmds[pnum][0], &cmds[pnum][1], env) == -1)
		perror(cmds[pnum][0]);
	exit(1);
}

void	last_child(int ac, char **av, int **pipes, char ***cmds)
{
	int		i;
	int		fd_file2;
	char	*env[1];

	env[0] = NULL;
	i = -1;
	while (++i < ac - 5)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
	close(pipes[ac - 5][1]);
	fd_file2 = open(av[ac - 1], O_TRUNC | O_WRONLY | O_CREAT, 0777);
	dup2(pipes[ac - 5][0], 0);
	dup2(fd_file2, 1);
	close(fd_file2);
	close(pipes[ac - 5][0]);
	if (execve(cmds[ac - 4][0], &cmds[ac - 4][1], env) == -1)
		perror(cmds[ac - 4][0]);
	exit(1);
}
