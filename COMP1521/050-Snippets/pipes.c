#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    pid_t pid;
    int retval;
    int fd[2];
    int n;

    retval = pipe(fd);
    if(retval < 0) {
        printf("Pipe failed\n");
        return 1;
    }

    pid = fork();
    if(pid == 0) {
        close(fd[0]);
        n = write(fd[1], "Hello from the child", 20);
        exit(0);
    }else{
        char buffer[64];
        close(fd[1]);
        n = read(fd[0], buffer, 64);
        buffer[n] = '\0';
        printf("The message received was: %s\n", buffer);
    }
    return 0;
}
