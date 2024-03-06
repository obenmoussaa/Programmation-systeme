#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <pthread.h>
#include "utils.h"

#define NUMBER_THREAD 8 

static int global = 0;
void *start(void *pid) {
    int local = 0;
    local++;
    global++;
    printf("variable globale : %d %p\n", global, &global);
    printf("varibale locale: %d %p\n", local, &local);
    printf("le pid du processus %p\n", pid);
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    pthread_t thread[NUMBER_THREAD];
    for (int i = 0; i < NUMBER_THREAD; i++) {
        pid_t pid = getpid();
        pthread_create(&thread[i], NULL, start, &pid);

    }
     for (int i = 0; i < NUMBER_THREAD; i++) {
        pthread_join(thread[i],NULL);
    }
    return EXIT_SUCCESS;
}



// thread =! fork si on attend pas le pere pour le thread ils meurent ce qui est pas le cas pour le fork.
