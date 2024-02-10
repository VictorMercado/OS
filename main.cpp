// #include <stdlib.h>
// #include <stdio.h>
// int glob1, glob2;

// int func2(){
//   int f2_local1, f2_local2;
//   printf("func2_local:\n\t%p, \n\t%p\n", &f2_local1, &f2_local2);
// }

// int func1(){
//   int f1_local1, f1_local2;
//   printf("func1_local:\n\t%p, \n\t%p\n", &f1_local1, &f1_local2);
//   func2();
// }

// int main(){
//   int m_local1, m_local2;
//   int *dynamic_addr;
//   printf("main_local:\n\t%p, \n\t%p\n", &m_local1, &m_local2);
//   func1();
//   dynamic_addr = (int *)malloc(16);
//   printf("dynamic: \n\t%p\n", dynamic_addr);
//   printf("global:\n\t%p, \n\t%p\n", &glob1, &glob2);
//   printf("functions:\n\t%p, \n\t%p, \n\t%p\n", main, func1, func2);
// }

// #include <sys/types.h>
// #include <unistd.h>
// #include <stdio.h>
// #include <stdlib.h>

// int g = 2;
// int main(void)
// {
//     pid_t pid;
//     int l = 3;
//     printf("process id(%d): parent g=%d, l=%d\n", getpid(), g, l);
//     if((pid=fork())<0){
//         perror("fork error");
//         exit(1);
//     } else if(pid == 0) {
//         g++;
//         l++;
//         printf("I am a new child and my procedd id is: %d \n", getpid());
//         printf("My parent process id is: %d \n", getppid());
//         printf("\n The child process now terminates");
//     } else {
//         g = g * 100;
//         l = l * 300;
//         printf("I am the PARENT process and my procedd id is: %d \n", getpid());
//         printf("Parent process id of the Parent Process is: %d \n", getppid());
//         printf("\n The parent process now terminates");
//     }
//     printf("\n\n ..... Who Am I ?? (%d): g=%d, l=%d\n", getpid(), g, l); //statement A
//     printf("\n\n ..... Who is my parent ?? (%d) \n ", getppid()); //statement B
//     return 0;
// }

// int main()
// {
//     pid_t pid;
//     /* fork another process */
//     pid = fork();
//     if (pid < 0) { /* error occurred */
//         fprintf(stderr, "Fork Failed");
//         exit(-1);
//     } else if (pid == 0) { /* child process */
//         execlp("/bin/ls", "ls", NULL);
//     } else { /* parent process */
//     /* parent will wait for the child to
//     complete */
//         wait (NULL);
//         printf ("Child Complete");
//         exit(0);
//     }
// }



// #include <cstdlib> // For std::system
// #include <iostream>
// using namespace std;

// int main() {
//     // Command to execute (replace with your desired command)
//     const char* command = "ls -l";

//     // Execute the command
//     int result = std::system(command);

//     // Check if the command executed successfully
//     if (result == 0) {
//         std::cout << "Command executed successfully.\n";
//     } else {
//         std::cout << "Command failed to execute.\n";
//     }

//     return 0;
// }


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
        execl("./fork", "fork", "-l", (char *)0);
        printf("Can I print out after execl ...?? \n");
    } else {
        pid = wait(&exit_status);
        printf("\n\nI am the parent of fork_exec and my process id is: %d\n", getpid());
    }
    return 0;
}
