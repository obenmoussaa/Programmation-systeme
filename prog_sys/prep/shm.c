#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include"utils.h"
#define FILE_PATH "/etc/bashrc"
#define SIZE 1024

int main() {
    key_t key;
    int shmid;
    void *shm_ptr;
    // Création d'une clé IPC avec ftok
    key = ftok("/etc/bash.bashrc" , 'R');
    exit_if(key == -1, "ftok");
    //shmget
    shmid = shmget(key, SIZE, IPC_CREAT | 0644);
    exit_if( shmid == -1, "shmid");
    //shmadd
    
    shm_ptr = shmat(shmid, NULL, 0);
    exit_if (shm_ptr == (void *)(-1), "shmmat");
    *((int *)shm_ptr)+=1;
    printf("Valeur incrémentée : %d\n", *((int *)shm_ptr));
    
    
    shmctl( shm_ptr, IPC_RMID, NULL);
    exit_if(shmdt(shm_ptr) == -1, "shmd");
    exit(EXIT_SUCCESS);
}

