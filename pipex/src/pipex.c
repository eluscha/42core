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

void	free_arrays(char ***cmds, int len)
{
	int	i;
	int	j;

	i = -1;
	while (++i < len)
	{
		if (!cmds[i])
			continue ;
		if (cmds[i][0])
			free(cmds[i][0]);
		j = 1;
		while (cmds[i][j])
			free(cmds[i][j++]);
		free(cmds[i]);
	}
	free(cmds);
	return ;
}

int	**create_pipes(int ac)
{
	int	**pipes;
	int i;

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

char **fill_cmd(char *cmd_str, char **envp)
{
	char **cmd_args;
	char **ret_ptr;
	int i;

	cmd_args = ft_split(cmd_str, ' ');
	if (!cmd_args)
		return (NULL);
	i = 0;
	while (cmd_args[i])
		i++;
	ret_ptr = malloc(sizeof(char *) * (i + 2));
	if (!ret_ptr)
	{
		free(cmd_args);
		return (NULL);
	}
	ret_ptr[0] = get_cmd(cmd_args[0], envp);;
	i = -1;
	while (cmd_args[++i]) 
		ret_ptr[i + 1] = cmd_args[i];
	ret_ptr[i + 1] = NULL;
	free(cmd_args);
	return (ret_ptr);
}

char	***create_arrays(int ac, char **av, char **envp)
{
	char	***cmds;
	int		i;

	cmds = ft_calloc(ac - 3, sizeof(char **));
	if (!cmds)
	{
		ft_printf("failed ft_calloc\n");
		return(NULL);
	}
	i = -1;
	while (++i < ac - 3)
		cmds[i] = fill_cmd(av[2 + i], envp);
	return cmds;
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
	char	***cmds;
	int		pipe_num;
	int		pid;

	if (argc < 5)
	{
		ft_printf("Invalid number of arguments\n");
		exit(1);
	}
	pipes = create_pipes(argc);
	cmds =  create_arrays(argc, argv, envp);
	if (!cmds)
	{
		free_pipes(pipes, argc);
		exit(1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Fork: ");
		free_pipes(pipes, argc);
		exit(1);
	}
	if (pid == 0)
		first_child(argc, argv, pipes, cmds, envp);
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
			mid_child(pipe_num, argc, pipes, cmds, envp);
		pipe_num++;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Fork: ");
		exit(1);
	}
	if (pid == 0)
		last_child(argc, argv, pipes, cmds, envp);
	close_pipes(-1, argc - 4, pipes);
	free_arrays(cmds, argc - 3);
	free_pipes(pipes, argc); 
	if (wait(NULL) != -1 || errno != ECHILD)
		return (-1);
	return (0);
}
