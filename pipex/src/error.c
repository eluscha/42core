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

void    pipe_error()
{

}

void    fork_error(int ac, int **pipes, char ***cmds)
{
    close_pipes(-1, ac - 4, pipes);
	free_arrays(cmds, ac - 3);
	free_pipes(pipes, ac); 
	perror("Fork: ");
	exit(1);
}

void    check_argc(int ac)
{
    if (ac > 4)
		return ;
	ft_printf("Invalid number of arguments\n");
	exit(1);
}