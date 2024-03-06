#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>
#include "utils.h"

void *ma_fonction_thread(void *arg) {
    intptr_t nbsec = (intptr_t)arg;
    printf("Je suis un thread et j'attends %ld secondes\n", (long)nbsec);
    sleep((unsigned int)nbsec);
    puts("Je suis un thread et je me termine");
    pthread_exit(NULL);
}

int main(void) {
    int ret;
    pthread_t my_thread;
    intptr_t nbsec;
    time_t t1;

    srand(time(NULL));
    t1 = time(NULL);
    nbsec = rand() % 10;

    ret = pthread_create(&my_thread, NULL, ma_fonction_thread, (void *)nbsec);
    if (ret != 0) {
        fprintf(stderr, "Erreur de création du thread\n");
        exit(1);
    }

    pthread_join(my_thread, NULL);

    printf("Dans le main, nbsec = %ld\n", (long)nbsec);
    printf("Durée de l'opération = %ld\n", (long)(time(NULL) - t1));

    return 0;
}

