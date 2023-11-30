#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main() {
    int fd; // store file descripter 0 - standard input, 1 - standard otpt, 2 - standard error
    char buffer[50];
    char msg[50] = "hello ifocus institute";

    fd = open("new.txt", O_RDWR);

    if (fd != -1) {
        printf("fd = %d\n", fd);
        printf("new.txt opened with read write access\n");

        write(fd, msg, sizeof(msg));

        lseek(fd, 0, SEEK_SET);

        read(fd, buffer, sizeof(msg));

        printf("%s was written to my file\n", buffer);

        close(fd);
    } else {
        perror("open");
    }

    return 0;
}

