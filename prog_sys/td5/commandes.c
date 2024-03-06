#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "sys/wait.h"
#include "utils.h"
#define MAX_READ 500

int main(int argc, char *argv[])
{
    char  *ls[] = { "ls", "-l", NULL};
    char  *tr[] = { "tr", "-d", "[:blank:]", NULL};
    char  *wc[] = { "wc", "-c", NULL};
    char **commandes[] = { ls, tr, wc};
    int nb_commandes = sizeof(commandes) / sizeof(char*);
    
    int pipe_fd[2];
    int s;
    int backup;
    int read_fd;
    int write_fd; 
    for (int i = 0; i < nb_commandes; i++) {
        if (i != nb_commandes-1) {
            exit_if(pipe(pipe_fd), "[+] Error pipe");
        }
        read_fd = pipe_fd[0];
        write_fd = pipe_fd[1];
        if (i < nb_commandes-1) {
            close(write_fd);
            backup = read_fd;
        }
        if (i > 0) {
            close(backup);
        }
        pid_t pid = fork();
        if ( pid == 0 ) {
            close(read_fd);
            if (i != nb_commandes-1 && i != 0) {
                dup2(write_fd, 1);
            } else {
                dup2(backup, 0);
            }
            close(write_fd);
            execvp(commandes[i][0], commandes[i]);
            return EXIT_FAILURE;
        }
	waitpid(pid, &s,0);
    }
    return EXIT_SUCCESS;
}

