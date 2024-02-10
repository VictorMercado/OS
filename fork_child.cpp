#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int g = 2;
int main(void)
{
    pid_t pid;
    int l = 3;
    printf("process id(%d): parent g=%d, l=%d\n", getpid(), g, l);
    if((pid=fork())<0){
        perror("fork error");
        exit(1);
    } else if(pid == 0) {
        g++;
        l++;
        printf("I am a new child and my procedd id is: %d \n", getpid());
        printf("My parent process id is: %d \n", getppid());
        printf("\n The child process now terminates");
    } else {
        g = g * 100;
        l = l * 300;
        printf("I am the PARENT process and my procedd id is: %d \n", getpid());
        printf("Parent process id of the Parent Process is: %d \n", getppid());
        printf("\n The parent process now terminates");
    }
    printf("\n\n ..... Who Am I ?? (%d): g=%d, l=%d\n", getpid(), g, l); //statement A
    printf("\n\n ..... Who is my parent ?? (%d) \n ", getppid()); //statement B
    return 0;
}