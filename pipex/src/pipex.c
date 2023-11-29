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
	int		onepipe[2];
	t_cmd	*cmd;
	pid_t	pid;

	check_argc(argc);
	if (pipe(onepipe) == -1)
	{
		perror("Pipe");
		exit(EXIT_FAILURE);
	}
	cmd = init_struct(argv, envp);
	check_init_error(cmd, onepipe);
	pid = fork();
	check_fork_error(pid, onepipe, cmd);
	if (pid == 0)
		first_child(cmd, onepipe);
	pid = fork();
	check_fork_error(pid, onepipe, cmd);
	if (pid == 0)
		last_child(cmd, onepipe);
	close(onepipe[0]);
	close(onepipe[1]);
	wait_cleanup_exit(pid, cmd);
}

void	check_argc(int ac)
{
	if (ac == 5)
		return ;
	ft_putstr_fd("Invalid number of arguments\n", 2);
	exit(EXIT_FAILURE);
}

void	wait_cleanup_exit(pid_t pid, t_cmd *cmd)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	while (wait(NULL) != -1)
		continue ;
	free(cmd);
	exit(WEXITSTATUS(status));
}
