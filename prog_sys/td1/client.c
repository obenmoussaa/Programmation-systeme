#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 100



void transfer(int fd_in, int fd_out) {
    char buffer[BUFFER_SIZE];
    ssize_t len_read, wrote, rc;

    while (1) {
        len_read = read(fd_in, buffer, BUFFER_SIZE);
        
        if (len_read == -1) {
            perror("Erreur lors de la lecture");
            exit(EXIT_FAILURE);
        }

        if (len_read == 0) {
            /* EOF*/
            return;
        }

        wrote = 0;

        do {
            rc = write(fd_out, buffer + wrote, len_read - wrote);

            if (rc == -1) {
                perror("Erreur lors de l'écriture");
                exit(EXIT_FAILURE);
            }

            wrote += rc;
        } while (wrote < len_read);
    }
}

int main() {
    int fd;
    char message[BUFFER_SIZE];
    ssize_t len_read;

    // Ouvrir la FIFO en écriture
    fd = open("versserveur", O_WRONLY);

    if (fd == -1) {
        perror("Erreur lors de l'ouverture de la FIFO en écriture");
        exit(EXIT_FAILURE);
    }

    printf("Entrez un message : ");
    len_read = read(STDIN_FILENO, message, BUFFER_SIZE);

    if (len_read == -1) {
        perror("Erreur lors de la lecture depuis l'entrée standard");
        exit(EXIT_FAILURE);
    }

    // Utiliser la fonction de transfert pour écrire le message dans la FIFO
    transfer(STDIN_FILENO, fd);

    // Fermer la FIFO
    close(fd);

    return 0;
}
