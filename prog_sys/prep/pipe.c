#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include"utils.h"




void transfere(int fd_in, int fd_out, int buffer_size){
        close(fd_in);
        char buffer[buffer_size];
        ssize_t rc = read(fd_out, buffer, buffer_size);
        exit_if (rc == -1, "read");
        write(STDOUT_FILENO, buffer, rc);
        close(fd_out);
}


int main(int argc, char* argv[]) {
    int nb = atoi(argv[1]);
    int tube[2]; // 2 file descriptor 
    exit_if( pipe(tube) == -1, "pipe"); 
    pid_t pid=fork();
    switch (pid)
    {
    case -1:
        exit_if(1, "fork");
    case 0:
        transfere(tube[1], tube[0], 500);
        fprintf(stderr, "Je suis le fils et je quitte\n");
        break;
    default:
        close(tube[0]); // j'ai pa bien compris pourquoi on ferme le tube avant d'écrire
        const char* message = "HelloWorld";
        size_t messageLength = strlen(message);
        for (int i = 0; i < nb; i++) {
            write(tube[1], message, messageLength);
            write(tube[1], "\n", 1);
         }
        close(tube[1]);
        fprintf(stderr, "Je suis le pere et je quitte\n");
            
        break;
        
    }
    return EXIT_SUCCESS;
}

