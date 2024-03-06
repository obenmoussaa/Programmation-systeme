#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

#include "utils.h"

#define THREAD_CONS_POOL 1
#define THREAD_PROD_POOL 1

#define POOL 2
#define SIZE 10000
#define LOOP 10

pthread_mutex_t fastmutex = PTHREAD_MUTEX_INITIALIZER;
sem_t empty_cell;
sem_t filled_cell;

/* Opaque function used by the consumer that should not be modified */
int consommer(int *value)
{
    usleep(10);
    //    fprintf( stderr, "Je lis\n");
    return *value;
}

/* Opaque function used by the producer that should not be modified */
void produire(int v, int *value)
{
    usleep(1);
    (*value) += v;
    //    fprintf( stderr, "J'ecris\n");
}

int A[SIZE];
int sum;

/* Function executed by a consumer */
void *
consommateur(void *ptr)
{
    int i, j;
    for (i = 0; i < LOOP; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            sem_wait(&filled_cell);
            sum += consommer(A + j);
            sem_post(&empty_cell);
        }
    }
    return NULL; // Equivalent a pthread_exit(NULL)
}

/* Function executed by a producer */
void *
producteur(void *ptr)
{
    int i, j;

    for (i = 0; i < LOOP; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            sem_wait(&empty_cell);
            produire(1, A + j);
            sem_post(&filled_cell);
        }
    }
    printf("J'ai fini d'ecrire\n");
    return NULL; // Equivalent a pthread_exit(NULL)
}

int main(int argc, char *argv[])
{
    sem_init(&empty_cell, 0, SIZE);
    sem_init(&filled_cell, 0, 0);

    pthread_t thread_cons[THREAD_CONS_POOL];
    pthread_t thread_prod[THREAD_PROD_POOL];

    /* Make sure the array is set to 0 */
    memset(A, 0, SIZE * sizeof(int));
    sum = 0;

    /* Create threads to execute these two functions in parallel with a guaranty of a correct result */
    for (int i = 0; i < THREAD_CONS_POOL; i++)
    {
        pthread_create(&thread_cons[i], NULL, consommateur, NULL);
    }

    for (int i = 0; i < THREAD_PROD_POOL; i++)
    {
        pthread_create(&thread_prod[i], NULL, producteur, NULL);
    }

    for (int i = 0; i < THREAD_CONS_POOL; i++)
    {
        pthread_join(thread_cons[i], NULL);
    }

    for (int i = 0; i < THREAD_PROD_POOL; i++)
    {
        pthread_join(thread_prod[i], NULL);
    }

    printf("La somme est de %d et devrait être de %d\n",
           sum, (LOOP * (LOOP + 1) / 2) * SIZE);

    sem_destroy(&empty_cell);
    
    sem_destroy(&filled_cell);

    return EXIT_SUCCESS;
}
