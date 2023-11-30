#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

void processRelatedCalls() {
    pid_t childPid;

    printf("Process Related System Calls\n");

    // Forking a child process
    childPid = fork();

    if (childPid == 0) {
        // Child process
        printf("Child Process: PID=%d, Parent PID=%d\n", getpid(), getppid());
        exit(0);
    } else if (childPid > 0) {
        // Parent process
        printf("Parent Process: PID=%d, Created Child PID=%d\n", getpid(), childPid);

        // Waiting for the child to complete
        wait(NULL);
        printf("Child Process Completed\n");
    } else {
        perror("Fork failed");
    }
}

void fileRelatedCalls() {
    int fileDescriptor;
    char buffer[50];
    ssize_t bytesRead;

    printf("\nFile Related System Calls\n");

    // Open a file
    fileDescriptor = open("example.txt", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

    if (fileDescriptor == -1) {
        perror("File open failed");
        return;
    }

    // Write to the file
    write(fileDescriptor, "Hello, World!\n", 13);

    // Move the file cursor to the beginning
    lseek(fileDescriptor, 0, SEEK_SET);

    // Read from the file
    bytesRead = read(fileDescriptor, buffer, sizeof(buffer));

    printf("Read from file: %.*s", (int)bytesRead, buffer);

    // Close the file
    close(fileDescriptor);
}

void protectionRelatedCalls() {
    printf("\nProtection Related System Calls\n");

    // Change file permissions
    if (chmod("example.txt", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) == -1) {
        perror("chmod failed");
    }
}

int main() {
    processRelatedCalls();
    fileRelatedCalls();
    protectionRelatedCalls();

    return 0;
}

