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

char	*get_cmd(char *cmd, char **envp)
{
	char	**dirs;
	char	*slash_cmd; 
	char	*full_cmd;
	int		i;

	slash_cmd = ft_strjoin("/", cmd); //free in the end
	while (*envp)
	{
		if (ft_strncmp((const char *) *envp, "PATH=", 5) == 0)
			break ;
		envp++;
	}
	if (!*envp)
	{
		free(slash_cmd);
		return (NULL);
	}
	dirs = ft_split(*envp, ':'); //free in the end
	i = 0;
	while (dirs[i])
	{
		full_cmd = ft_strjoin(dirs[i++], slash_cmd);
		if (access(full_cmd, X_OK) == 0)
			break ;
		free(full_cmd);
	}
	if (!dirs[i])
		full_cmd = NULL;
	free(slash_cmd);
	i = 0;
	while (dirs[i])
		free(dirs[i++]);
	free(dirs);
	return (full_cmd);
}

void	free_arrays(char ***cmd_args, char **full_cmd, int len)
{
	int	i;
	int	j;

	i = 0;
	while (i < len)
	{
		if (full_cmd[i])
			free(full_cmd[i]);
		j = 0;
		if (cmd_args[i])
		{
			while (cmd_args[i][j])
				free(cmd_args[i][j++]);
			free(cmd_args[i]);
		}
		i++;
	}
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	int		pipes[argc - 4][2];
	char	**cmd_args[argc - 3];
	char	*full_cmd[argc - 3];
	char	*env[1];
	int		pipe_num;
	int		i;
	int		pid;

	env[0] = NULL;
	if (argc < 5)
	{
		printf("Invalid number of argumets\n");
		return (1);
	}
	i = 0;
	while (i < argc - 4)
	{
		if (pipe(pipes[i++]) == -1)
		{
			printf("%s\n", strerror(errno));
			return (1);
		}
	}
	i = 0;
	while (i < argc - 3)
	{
		cmd_args[i] = ft_split(argv[2 + i], ' ');
		full_cmd[i] = get_cmd(cmd_args[i][0], envp);
		i++;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Fork: ");
		exit(1);
	}
	if (pid == 0)
	{
		//Child1
		i = 0;
		while (++i < argc - 4)
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
		}

		close(pipes[0][0]); //we do not need to read from pipe
		int fd_file1 = open(argv[1], O_RDONLY);
		if (fd_file1 == -1)
		{
			perror(argv[1]);
			exit(1);
		}
		dup2(fd_file1,0); //instead of stdin will be file1
		dup2(pipes[0][1],1); //instead of stdout will be first pipe write end
		close(fd_file1);
		close(pipes[0][1]);
		if (execve(full_cmd[0], cmd_args[0], env) == -1)
			perror(argv[2]);
		exit(1);
	}
	pipe_num = 1;
	while (pipe_num < argc - 4)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("Fork: ");
			exit(1);
		}	
		if (pid == 0)
		{
		//Child_mid
			i = -1;
			while (++i < pipe_num - 1)
			{
				close(pipes[i][0]);
				close(pipes[i][1]);
			}
			i++;
			while (++i < argc - 4)
			{
				close(pipes[i][0]);
				close(pipes[i][1]);
			}
			close(pipes[pipe_num - 1][1]);
			close(pipes[pipe_num][0]);
			dup2(pipes[pipe_num - 1][0],0); //instead of stdin will be pipe read end
			dup2(pipes[pipe_num][1], 1); //instead of stdout will be pipe write end
			close(pipes[pipe_num][0]);
			close(pipes[pipe_num][1]);
			if (execve(full_cmd[pipe_num], cmd_args[pipe_num], env) == -1)
				perror(argv[pipe_num + 2]);
			exit(1);
		}
		pipe_num++;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Fork: ");
		exit(1);
	}
	if (pid == 0)
	{
		//Child_last
		i = -1;
		while (++i < pipe_num - 1)
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
		}
		close(pipes[pipe_num - 1][1]);
		int fd_file2 = open("file2", O_TRUNC | O_WRONLY | O_CREAT, 0777);
		dup2(pipes[pipe_num - 1][0],0); //instead of stdin will be pipe read end
		dup2(fd_file2, 1); //instead of stdout will be file2
		close(fd_file2);
		close(pipes[pipe_num - 1][0]);
		if (execve(full_cmd[pipe_num], cmd_args[pipe_num], env) == -1)
			perror(argv[pipe_num + 2]);
		exit(1);
	};
	i = -1;
	while (++i < argc - 4)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
	free_arrays(cmd_args, full_cmd, argc - 3); 
	if (wait(NULL) != -1 || errno != ECHILD)
		return (-1); //waits for any 1 child, ideally should be changed to wait for both
	return (0);
}