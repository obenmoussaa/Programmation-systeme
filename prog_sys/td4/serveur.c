#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER_SIZE 100

int main() {


    char buffer[BUFFER_SIZE];
    ssize_t rc;
    mknod("versserveur", S_IFIFO | 0666, 0);
    int fd_fifo = open("versserveur", O_RDONLY);

    if (fd_fifo == -1) {
        perror("Erreur lors de l'ouverture de la FIFO");
        return 1;
    }
    

    while ((rc = read(fd_fifo, buffer, sizeof(buffer))) > 0) {
        write(1, buffer, rc);
    }

    // Fermer la FIFO
    close(fd_fifo);

    return 0;
}
