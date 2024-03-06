#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <pthread.h>

#include <semaphore.h>
 #include <fcntl.h>
#include <sys/stat.h>

#include "utils.h"

#define POOL 8








int nbtickets = 1000;
sem_t *sem;
void *vendeur( void* arg )
{
    int id = (int)(intptr_t) arg;
    int nbtickets_vendus = 0;
    int b = 0;
    while ( b == 0 ) {
        if ( sem_trywait(sem) != -1) {
	        nbtickets_vendus++;
	        sched_yield(); /* Do not touch this line */
        } else {
            b = 1;
        }
    }
    
    printf( "[%d] J'ai vendu %d tickets \n",
	    id, nbtickets_vendus );
    
    return (void *) (intptr_t)nbtickets_vendus;
}

int
main( int argc, char *argv[] ) {
    int nbtickets_vendus = 0;
    pthread_t threads[POOL];
    void *r;
    int i;
    sem = sem_open("semaphore", O_CREAT, 0600, 1);
    sem_init(sem, 0, nbtickets);
    for (i = 0; i < 8; i++) {
        pthread_create(&threads[i], NULL, vendeur, (void *)(intptr_t)i);
    }
    for (i = 0; i < POOL; i++) {
        pthread_join(threads[i], &r);
        nbtickets_vendus += (int)(intptr_t)r;
    }
    printf( "%d tickets ont été vendus (nbtickets = %d)\n",
	    nbtickets_vendus, nbtickets );
    sem_destroy(sem);
    return EXIT_SUCCESS;
}

