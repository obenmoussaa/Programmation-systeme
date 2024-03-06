#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include"utils.h"
sem_t semaphore;

void* ma_fonction_thread(void *arg);

int main(int argc, char **argv)
{
    int i;
    pthread_t thread[10];

    srand(time(NULL));

    if (argc != 2)
    {
        printf("Usage : %s nbthreadmax\n", argv[0]);
        exit(0);
    }

    sem_init(&semaphore, 0, atoi(argv[1]));

    for (i = 0; i < 10; i++)
        pthread_create(&thread[i], NULL, ma_fonction_thread, (void*)i);

    for (i = 0; i < 10; i++)
        pthread_join(thread[i], NULL);

    sem_destroy(&semaphore);
    return 0;
}

void* ma_fonction_thread(void *arg)
{
    int num_thread = (int)arg;
    int nombre_iterations, i;

    nombre_iterations = rand() % 8 + 1;

    for (i = 0; i < nombre_iterations; i++)
    {
        sem_wait(&semaphore);
        printf("Le thread %d entre dans la section critique\n", num_thread);
        sleep(rand() % 9 + 1);
        printf("Le thread %d sort de la section critique\n", num_thread);
        sem_post(&semaphore);
        sleep(rand() % 9 + 1);
    }

    pthread_exit(NULL);
}

