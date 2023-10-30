

#include "pipex.h"

void	first_child(int ac, char **av, int **pipes, char ***cmds, char **envp)
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
    if (execve(cmds[0][0], &cmds[0][1], envp) == -1)
		perror(cmds[0][0]);
	exit(1);
}

void	mid_child(int pnum, int ac, int **pipes, char ***cmds, char **envp)
{
	int	i;

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
	dup2(pipes[pnum - 1][0],0); //instead of stdin will be pipe read end
	dup2(pipes[pnum][1], 1); //instead of stdout will be pipe write end
	close(pipes[pnum][0]);
	close(pipes[pnum][1]);
    if (execve(cmds[pnum][0], &cmds[pnum][1], envp) == -1)
		perror(cmds[pnum][0]);
	exit(1);
}

void	last_child(int ac, char **av, int **pipes, char ***cmds, char **envp)
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
    if (execve(cmds[ac - 4][0], &cmds[ac - 4][1], envp) == -1)
		perror(cmds[ac - 4][0]);
	exit(1);
}
