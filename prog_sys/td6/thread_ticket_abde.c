#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>

#include "utils.h"

#define POOL 8

int nbtickets = 1000;

#define SEM_NAME "semaphore"
sem_t  semaphore;
sem_t *semptr;

void *
thread_function(void *arg)
{
    int nbtickets_vendus = 0;
    int i = (intptr_t)arg;
    
    while ( sem_trywait( semptr ) == 0 ) {
	nbtickets_vendus++;
	
	sched_yield();
    }
    
    printf( "[%d] J'ai vendu %d tickets \n",
	    i, nbtickets_vendus );
    
    pthread_exit( (void*)((intptr_t)nbtickets_vendus) );
}

int
main( int argc, char *argv[] ) {
    pthread_t thrdids[POOL];
    int i;
    int nbtickets_vendus = 0;

    if ( argc >= 2 ) {
	nbtickets = atoi( argv[1] );
    }

    /* Initialize the semaphore with the number of tickets available */
#if defined(WITH_SEM_INIT)
    exit_if( sem_init( &semaphore, 0, nbtickets ) == -1, "sem init" );
    semptr = &semaphore;
#else
    semptr = sem_open( SEM_NAME, O_CREAT, 0666, nbtickets );
    exit_if( semptr == SEM_FAILED, "sem open" );
#endif

    /* Launch all the threads */
    for( i=0; i<POOL; i++) {
	pthread_create( thrdids + i, NULL,
			thread_function, (void*)((intptr_t)i) );
    }

    /* Wait for the end of all threads */
    for( i=0; i<POOL; i++) {
	void *tmp;
	pthread_join( thrdids[i], &tmp );
	nbtickets_vendus += (intptr_t)(tmp);
    }
    
    printf( "%d tickets ont été vendus sur %d disponibles\n",
	    nbtickets_vendus, nbtickets );
    
#if defined(WITH_SEM_INIT)
    sem_destroy( semptr );
#else
    sem_unlink( SEM_NAME );
    sem_close( semptr );
#endif
    return EXIT_SUCCESS;
}
