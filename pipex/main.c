//#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
//#include 

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
        char *args[] = {"ls", "-l", NULL};
        char *env[] = {NULL};
        dup2(fd[1],1);
        if (execve("/usr/bin/ls", args, env) == -1)
            perror("Could not execve");
    }
    else
    {
        wait(NULL);
        int fd_file2 = open("file2", O_WRONLY);
        char *args[] = {"wc", "-l", NULL};
        char *env[] = {NULL};
        dup2(fd[0],0);
        dup2(fd_file2, 1);
        if (execve("/usr/bin/wc", args, env) == -1)
            perror("Could not execve");
    }
}