#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "utils.h"
#define BUFFER_SIZE 100

#define FIFONAME "verserveur"



int main() {
    int fd;
    //char mes[BUFFER_SIZE];
    fd = open(FIFONAME, O_WRONLY);
    //rc = read(STDIN_FILENO, mes, BUFFER_SIZE);
    exit_if(fd == -1, "open fifo");
    transfer(STDIN_FILENO, fd, 128);
    close(fd);

    return 0;
}
