#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    int pipefd[2];
    
    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }
    
    pid_t pid = fork();
    
    if (pid == -1) {
        perror("fork");
        return 1;
    }
    
    if (pid == 0) {  // Child process
        // Close the write end of the pipe
        close(pipefd[1]);
        
        // Redirect the read end of the pipe to stdin (file descriptor 0)
        dup2(pipefd[0], 0);
        
        // Close the original read end of the pipe
        close(pipefd[0]);
        
        // Now you can use wc or any other command that reads from stdin
        execlp("wc", "wc", "-l", NULL);
        perror("execlp");
        return 1;
    } else {  // Parent process
        // Close the read end of the pipe
        close(pipefd[0]);
        
        dup2(pipefd[1],1);

        close(pipefd[1]);

        execlp("ls", "ls", "-l", NULL);
        perror("execlp");
    
        // Wait for the child process to finish
        wait(NULL);
    }
    
    return 0;
}

