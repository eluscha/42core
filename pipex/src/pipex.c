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
	{
		if (write_tmp_file(cmd) == -1)
			file_error(0, cmd, pipes, num_pipes);
	}
	pid = fork();
	check_fork_error(pid, pipes, num_pipes);
	if (pid == 0)
		first_child(cmd, pipes, num_pipes);
	bonus_loop(pipes, cmd, num_pipes);
	pid = fork();
	check_fork_error(pid, pipes, num_pipes);
	if (pid == 0)
		last_child(argv[argc - 1], cmd, pipes, num_pipes);
	wait_and_cleanup(pid, cmd, pipes, num_pipes);
}

int	write_tmp_file(t_cmd *cmd)
{
	int		fd;
	char	*line;
	char	*limiter;
	size_t	len;

	fd = open(".temp_hd", O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (fd == -1)
		return (-1);
	limiter = cmd->av[2];
	len = ft_strlen(limiter);
	line = get_next_line(0);
	while (line)
	{
		if (ft_strlen(line) == len + 1)
		{
			if (ft_strncmp(line, limiter, len) == 0)
				break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
    if (line)
		free(line);
	close(fd);
	return (0);
}

void	bonus_loop(int **pipes, t_cmd *cmd, int num_pipes)
{
	int		cnum;
	int		pid;

	cnum = 0;
	while (++cnum < num_pipes)
	{
		pid = fork();
		check_fork_error(pid, pipes, num_pipes);
		if (pid == 0)
			mid_child(cmd, cnum, pipes, num_pipes);
	}
	return ;
}

void	wait_and_cleanup(pid_t pid, t_cmd *cmd, int **pipes, int num_pipes)
{
	int	status;
	
	status = 0;
	close_pipes(pipes, 0, num_pipes);
	//printf("exit code is %i\n", status);
	waitpid(pid, &status, 0);
	//printf("exit code is %i\n", status);
	//printf("exit code is %i\n", errno);
	while (wait(NULL) != -1);
	free_pipes(pipes, num_pipes);
	if (cmd->here_doc)
		unlink(".temp_hd");
	free(cmd);
	printf("exit code is %i\n", WEXITSTATUS(status));
	exit(WEXITSTATUS(status));
}