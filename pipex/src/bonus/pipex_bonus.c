/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eusatiko <eusatiko@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:13:38 by eusatiko          #+#    #+#             */
/*   Updated: 2023/10/16 12:13:46 by eusatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
		write_tmp_file(cmd, pipes, num_pipes);
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
	wait_cleanup_exit(pid, cmd, pipes, num_pipes);
}

void	write_tmp_file(t_cmd *cmd, int **pipes, int num_pipes)
{
	int		fd;
	char	*limiter;
	char	*name;
	size_t	len;

	name = "/tmp/pipex_here_doc";
	fd = open(name, O_CREAT | O_EXCL | O_WRONLY | O_APPEND, 0777);
	if (fd == -1)
		file_error(0, cmd, pipes, num_pipes);
	limiter = cmd->av[2];
	len = ft_strlen(limiter);
	get_input(fd, limiter, len);
	close(fd);
	return ;
}

void	get_input(int fd, char *limiter, size_t len)
{
	char	*line;

	ft_putstr_fd("> ", 0);
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
		ft_putstr_fd("> ", 0);
		line = get_next_line(0);
	}
	if (line)
		free(line);
	return ;
}

void	wait_cleanup_exit(pid_t pid, t_cmd *cmd, int **pipes, int num_pipes)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	while (wait(NULL) != -1)
		continue ;
	if (cmd->here_doc)
		unlink("/tmp/pipex_here_doc");
	cleanup(cmd, pipes, num_pipes);
	exit(WEXITSTATUS(status));
}

void	cleanup(t_cmd *cmd, int **pipes, int num_pipes)
{
	if (cmd->adr || cmd->args)
		free_cmd(cmd);
	free(cmd);
	free_pipes(pipes, num_pipes);
	return ;
}
