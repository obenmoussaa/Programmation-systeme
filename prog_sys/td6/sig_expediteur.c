#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "utils.h"
#define FILE_SIZE 128


int fd;
void * mmap_ptr = NULL;
void handler(int sign)
{
    if (sign == SIGUSR1)
    {
        printf("mmap = %d\n", *((int *) mmap_ptr));
        exit_if(write(STDOUT_FILENO, mmap_ptr, FILE_SIZE) == -1, "write");
    }
}

int main(int argc, const char *argv[]){

    pid_t pid = getpid();
    printf("le pid est %d\n", pid);
    fd = open("fichier.txt" , O_RDWR);
    mmap_ptr = mmap(NULL, FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);//la taille minimale deu fichier est FILE_SIZE + OFFSET 
    exit_if(mmap_ptr == MAP_FAILED, "mmap");
    int valeur_pid = *((int * ) mmap_ptr);
    int rc = read(STDIN_FILENO, mmap_ptr, 128);
    exit_if(rc == -1, "read");
    int result = kill( valeur_pid, SIGUSR1);
    exit_if( result == -1, "kill");
    munmap(mmap_ptr, FILE_SIZE);
    return EXIT_SUCCESS;
}
