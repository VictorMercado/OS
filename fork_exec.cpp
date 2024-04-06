
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(void)
{
    pid_t pid;
    int exit_status;
    if((pid=fork())<0){
        perror("fork error");
        exit(1);
    } else if(pid == 0) {
        printf("Hi\n");
        execl("./helloworl", "helloworld", "", (char *)0);
        printf("Can I print out after execl ...?? \n");
    } else {
        pid = wait(&exit_status);
        printf("\n\nI am the parent of fork_exec and my process id is: %d\n", getpid());
    }
    return 0;
}
