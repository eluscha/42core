#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include "ft_split.c"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && i < n)
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	if (i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*((char *)s + i) != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*strcat;
	size_t	len1;
	size_t	len2;
	size_t	i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	strcat = malloc(len1 + len2 + 1);
	if (strcat == NULL)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		strcat[i] = s1[i];
		i++;
	}
	while (i < len1 + len2 + 1)
	{
		strcat[i] = s2[i - len1];
		i++;
	}
	return (strcat);
}

char *get_cmd(char *cmd, char **envp)
{
    char **dirs;
    char *slash_cmd = ft_strjoin("/", cmd); //free in the end
    char *full_cmd;
    while (*envp)
    {
        if (ft_strncmp((const char *) *envp, "PATH=", 5) == 0)
            break ;
        envp++;
    }
    if (!*envp)
    {
        free(slash_cmd);
        return NULL;
    }

    dirs = ft_split(*envp, ':'); //free in the end
    int i = 0;
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
    return full_cmd;
}


/*
int first_cmd(int argc, char **argv, char **envp, char ***args_adr, char **cmd_adr)
{
    
    char *env[] = {NULL};
    *args_adr = ft_split(argv[2], ' ');
    *cmd_adr = get_cmd(cmd_args[0], envp);
    int i = 0;
    if (full_cmd)
    {
        int pid = fork();
        if (pid == 0)
        {
            close(fd[0]);
            dup2(fd[1],1);
	        close(fd[1]);
            if (execve(full_cmd, cmd_args, env) == -1)
                perror("Could not execve");
        }
        wait(NULL);
        free(full_cmd);close(fd[1]);
        int fd_file2 = open("file2", O_WRONLY | O_CREAT, 0777);
        char *args[] = {"wc", "-l", NULL};
        char *env[] = {NULL};
        dup2(fd[0],0); //instead of stdin will be pipe read end
        dup2(fd_file2, 1); //instead of stdout will be file2
        close(fd_file2);
        close(fd[0]);
        if (execve("/usr/bin/wc", args, env) == -1)
            perror("Could not execve");
        return (-1);
    }
}


int last_cmd(int argc, char **argv, char **envp)
{
    char **cmd_args = ft_split(argv[argc - 2], ' ');
    char *full_cmd = get_cmd(cmd_args[0], envp);
    int i = 0;
    if (full_cmd)
    {
        int pid = fork();        {

        if (pid == 0)
        {
            char *env[] = {NULL};
            execve(full_cmd, cmd_args, env);
        }
        wait(NULL);
        free(full_cmd);
    }
    else
        printf("No such command!\n");
    while(cmd_args[i])
        free(cmd_args[i++]);
    free(cmd_args);
    return 1;
}
}
*/

int main(int argc, char **argv, char **envp)
{
    int pipes[argc - 4][2];
    int i = 0;
    while (i < argc - 4)
        pipe(pipes[i++]);
    
    char **cmd_args[argc - 3];
    char *full_cmd[argc - 3];
    i = 0;
    while (i < argc - 3)
    {
        cmd_args[i] = ft_split(argv[2 + i], ' ');
        full_cmd[i] = get_cmd(cmd_args[i][0], envp);
        i++;
    }
    char *env[] = {NULL};

    int pid = fork();
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
        dup2(fd_file1,0); //instead of stdin will be file1
        dup2(pipes[0][1],1); //instead of stdout will be first pipe write end
	    close(fd_file1);
        close(pipes[0][1]);
        if (execve(full_cmd[0], cmd_args[0], env) == -1)
            perror("Could not execve");
	    return (-1);
    }

    int pipe_num = 1;
    while (pipe_num < argc - 4)
    {
        printf("inside while loop \n");
        pid = fork();	
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
            perror("Could not execve");
        return (-1);
        }
        pipe_num++;
    }

    

    //wait(NULL);

    pid = fork();	
    if (pid == 0)
    {
        //Child_last
        printf("pipe_num is: %d\n", pipe_num);
        i = -1;
        while (++i < pipe_num - 1)
        {
            close(pipes[i][0]);
            close(pipes[i][1]);
        }

        close(pipes[pipe_num - 1][1]);
        int fd_file2 = open("file2", O_WRONLY | O_CREAT, 0777);
        dup2(pipes[pipe_num - 1][0],0); //instead of stdin will be pipe read end
        dup2(fd_file2, 1); //instead of stdout will be file2
        close(fd_file2);
        close(pipes[pipe_num - 1][0]);
        if (execve(full_cmd[pipe_num], cmd_args[pipe_num], env) == -1)
            perror("Could not execve");
        return (-1);
    };
    close(pipes[0][0]);
    close(pipes[0][1]);
    close(pipes[1][0]);
    close(pipes[1][1]);
    //free stuff! 
    if (wait(NULL) != -1 || errno != ECHILD)
        return (-1); //waits for any 1 child, ideally should be changed to wait for both
    return 0;
}