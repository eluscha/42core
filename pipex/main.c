//#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>


int main(void)
{
    //open(argv[1], R_ONLY);
    //open(argv[4], W_ONLY);
    int fd[2];
    pipe(fd);
    int pid = fork();
    if (pid == 0)
    {
        //Child1
        printf("I am child1\n");
	    close(fd[0]);
        char *args[] = {"ls", "-l", NULL};
        char *env[] = {NULL};
        dup2(fd[1],1);
	    close(fd[1]);
        if (execve("/usr/bin/ls", args, env) == -1)
            perror("Could not execve");
	    return (-1);
    }
    //printf("i am parent\n");
    pid = fork();	
    //printf("my pid is %d and pid1 is %d\n", pid, pid1);
    if (pid == 0)
    {
        //Child2
        printf("I am child2\n");
        close(fd[1]);
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
    //printf("child2 finished\n");
    close(fd[0]);
    close(fd[1]);
    if (wait(NULL) != -1 || errno != ECHILD)
        return (-1); //waits for any 1 child, ideally should be changed to wait for both
    return 0;
}
 