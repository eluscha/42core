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
	    close(fd[0]);
        char *args[] = {"ls", "-l", NULL};
        char *env[] = {NULL};
        dup2(fd[1],1);
	    close(fd[1]);
        if (execve("/usr/bin/ls", args, env) == -1)
            perror("Could not execve");
	    return (-1);
    }
    else
    {
        //wait(NULL);
        printf("Child1 finished\n");
        int pid1 = fork();	
        printf("my pid is %d and pid1 is %d\n", pid, pid1);
        if (pid1 == 0)
        {
            //Child2
            close(fd[1]);
            int fd_file2 = open("file2", O_WRONLY);
            char *args[] = {"wc", "-l", NULL};
            char *env[] = {NULL};
            dup2(fd[0],0); //instead of stdin will be pipe read end
            dup2(fd_file2, 1); //instead of stdout will be file2
            close(fd_file2);
            close(fd[0]);
            if (execve("/usr/bin/wc", args, env) == -1) // does not read from pipe :(
                perror("Could not execve");
            return (-1);
        }
        wait(NULL);
        printf("child2 finished\n");
        close(fd[0]);
        close(fd[1]);
        return 0;
    }
}
