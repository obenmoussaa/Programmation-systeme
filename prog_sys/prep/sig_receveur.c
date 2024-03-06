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

int main(int argc, const char *argv[])
{

    pid_t pid = getpid();
    printf("le pid est %d\n", pid);
    struct sigaction new_act;
    struct sigaction old_act;
    sigset_t sigset;
    sigset_t usrset;
    sigemptyset(&usrset);
    sigaddset(&usrset, SIGUSR1);
    sigprocmask(SIG_BLOCK, &usrset,NULL);

    exit_if(sigfillset(&new_act.sa_mask) == -1, "sigfillset");//cela initialise le champ sa_mask pour ne pas recevoir les signaux masques
    new_act.sa_handler = handler;
    new_act.sa_flags = 0;
    fd = open("fichier.txt" , O_RDWR);
    //changement de comportement
    exit_if(sigaction(SIGUSR1, &new_act, &old_act) == -1, "sigaction");
    exit_if(sigfillset(&sigset), "sigset");
    exit_if(sigdelset(&sigset, SIGUSR1), "sigset");
    mmap_ptr = mmap(NULL, FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);//la taille minimale deu fichier est FILE_SIZE + OFFSET 
    exit_if(mmap_ptr == MAP_FAILED, "mmap");
    *((int * ) mmap_ptr) = pid ;
    sigsuspend(&sigset);
    exit_if(sigprocmask(SIG_BLOCK, &usrset, NULL) == -1, "sigprocmask");
    munmap(mmap_ptr, FILE_SIZE);
    return EXIT_SUCCESS;
}
