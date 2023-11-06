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
	close_pipes(i, pipes);
	while (--i >= 0)
		free(pipes[i]);
	exit(EXIT_FAILURE);
}

void	fork_error(int ac, int **pipes, char ***cmds)
{
	close_pipes(ac - 4, pipes);
	free_arrays(cmds, ac);
	free_pipes(pipes, ac); 
	perror("Fork: ");
	exit(EXIT_FAILURE);
}

void	check_argc(int ac)
{
	if (ac > 4)
		return ;
	ft_printf("Invalid number of arguments\n");
	exit(EXIT_FAILURE);
}
