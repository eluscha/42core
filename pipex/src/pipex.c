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
	free(cmd_args);
	free(full_cmd);
	return ;
}

int	**create_pipes(int ac)
{
	int	**pipes;
	int i;

	pipes = ft_calloc(sizeof(int *), ac - 4);
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
		{
			ft_printf("pipes[%d]: failed malloc\n", i);
			break ;
		}
		else if (pipe(pipes[i++]) == -1)
		{
			printf("%s\n", strerror(errno));
			break;
		}
	}
	return (pipes);
}

void	free_pipes(int **pipes, int argc)
{
	int	i;

	i = 0;
	while (i < argc - 4)
	{
		if (!pipes[i])
			break ;
		else
			free(pipes[i++]);
	}
	free(pipes);
}

char	***create_arrays(int ac, char **av, char ***adr, char **envp)
{
	char	***cmd_args;
	char	**full_cmd;
	int		i;

	cmd_args = ft_calloc(sizeof(char **), ac - 3);
	full_cmd = ft_calloc(sizeof(char*), ac - 3);
	if (!cmd_args || !full_cmd)
	{
		ft_printf("failed ft_calloc\n");
		if (cmd_args)
			free(cmd_args);
		if (full_cmd)
			free(full_cmd);
		return(NULL);
	}
	i = 0;
	while (i < ac - 3)
	{
		cmd_args[i] = ft_split(av[2 + i], ' ');
		full_cmd[i] = get_cmd(cmd_args[i][0], envp);
		i++;
	}
	*adr = full_cmd;
	return cmd_args;
}

void	first_child(int ac, char **av, int **pipes)
{
	int	i;

	i = 0;
	while (++i < ac - 4)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
	close(pipes[0][0]); //we do not need to read from pipe
	int fd_file1 = open(av[1], O_RDONLY);
	if (fd_file1 == -1)
	{
		perror(av[1]);
		exit(1);
	}
	dup2(fd_file1,0); //instead of stdin will be file1
	dup2(pipes[0][1],1); //instead of stdout will be first pipe write end
	close(fd_file1);
	close(pipes[0][1]);
}

void	mid_child(int pipe_num, int ac, int **pipes)
{
	int	i;

	i = -1;
	while (++i < pipe_num - 1)
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
	close(pipes[pipe_num - 1][1]);
	close(pipes[pipe_num][0]);
	dup2(pipes[pipe_num - 1][0],0); //instead of stdin will be pipe read end
	dup2(pipes[pipe_num][1], 1); //instead of stdout will be pipe write end
	close(pipes[pipe_num][0]);
	close(pipes[pipe_num][1]);
}

void	last_child(int ac, char **av, int **pipes)
{
	int	i;

	i = -1;
	while (++i < ac - 5)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
		close(pipes[ac - 5][1]);
		int fd_file2 = open(av[ac - 1], O_TRUNC | O_WRONLY | O_CREAT, 0777);
		dup2(pipes[ac - 5][0],0); //instead of stdin will be pipe read end
		dup2(fd_file2, 1); //instead of stdout will be file2
		close(fd_file2);
		close(pipes[ac - 5][0]);
}

void	close_pipes(int start, int end, int **pipes)
{
	int i;

	i = start;
	while (++i < end)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		**pipes;
	char	***cmd_args;
	char	**full_cmd;
	int		pipe_num;
	int		pid;

	if (argc < 5)
	{
		ft_printf("Invalid number of argumets\n");
		return (1);
	}
	pipes = create_pipes(argc);
	cmd_args =  create_arrays(argc, argv, &full_cmd, envp);
	if (!cmd_args)
	{
		free_pipes(pipes, argc);
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Fork: ");
		exit(1);
	}
	if (pid == 0)
	{
		first_child(argc, argv, pipes);
		if (execve(full_cmd[0], cmd_args[0], envp) == -1)
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
			mid_child(pipe_num, argc, pipes);
			if (execve(full_cmd[pipe_num], cmd_args[pipe_num], envp) == -1)
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
		last_child(argc, argv, pipes);
		if (execve(full_cmd[pipe_num], cmd_args[pipe_num], envp) == -1)
			perror(argv[pipe_num + 2]);
		exit(1);
	};
	close_pipes(-1, argc - 4, pipes);
	free_arrays(cmd_args, full_cmd, argc - 3);
	free_pipes(pipes, argc); 
	if (wait(NULL) != -1 || errno != ECHILD)
		return (-1);
	return (0);
}
