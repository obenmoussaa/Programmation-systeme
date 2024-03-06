#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "utils.h"
#include <pthread.h>
#include <ctype.h>
#include <errno.h>
#include <sched.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int ticketsDisponibles = 1000;

#define NUM_THREADS 8


void *vendeur(void *arg)
{
    int id = *((int *) arg);
    int billetsVendus = 0;
 
    while (ticketsDisponibles > 0)
    {   pthread_mutex_lock(&mutex);
        billetsVendus++;
        sched_yield();
        ticketsDisponibles--;
        pthread_mutex_unlock(&mutex);
    }
    printf("Thread %d a vendu %d billets.\n", id, billetsVendus);
    int* return_value = (int * )malloc(sizeof(int));
    *return_value = billetsVendus;
    return return_value;
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int threadData[NUM_THREADS];

        for (int i = 0; i < NUM_THREADS; i++)
    {
        threadData[i] = 0;
        pthread_create(&threads[i], NULL, vendeur, (void *)&threadData[i]);
    }
    int totalBilletsVendus = 0;
    for (int i = 0; i < NUM_THREADS; i++)
    {
        void *result;
        pthread_join(threads[i], &result);
        totalBilletsVendus += *(int *)result;
    }
    printf("Nombre total de billets vendus : %d\n", totalBilletsVendus);

    return 0;
}
