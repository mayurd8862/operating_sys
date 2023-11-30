#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> // Include this header for the wait function

int main() {
    pid_t ret_value;

    printf("\nThe process id is %d\n", getpid());

    ret_value = fork();

    if (ret_value < 0) {
        // fork has failed
        printf("\nFork Failure\n");
    } 
    else if (ret_value == 0) {
        // child process
        printf("\nChild Process\n");
        printf("The process id is %d\n", getpid());
        // Uncomment the line below to add a delay in the child process
        sleep(3);
    } 
    else {
        // parent process
        wait(NULL); // Use wait here to wait for the child process to complete
        printf("Parent Process\n");
        printf("The process id is %d\n", getpid());
        // Uncomment the line below to add a delay in the parent process
        // sleep(30);
    }

    return 0;
}

