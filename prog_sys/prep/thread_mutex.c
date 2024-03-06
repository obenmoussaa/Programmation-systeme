#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <pthread.h>

#include "utils.h"

#define POOL 8

int nbtickets = 1000;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
/* La section critique est délimité par pthread_mutex_lock et pthread_mutex_unlock*/

/*cette section est protogée par un mutex, qui garantit qu'un seul thread à la fois 
peut accéder à cette section. Chaque thread qui veut accéder à la section critique 
doit d'abord verrouiller le mutex, puis déverrouiller le mutex une fois la section 
critique terminée. Cela permet de s'assurer que seul un thread à la fois peut accéder
 à la section critique et évite ainsi les problèmes de race*/
 
void *vendeur( void* arg )
{   //pthread_mutex_lock(&mutex);
    int id = (int)(intptr_t) arg;
    int nbtickets_vendus = 0;
    int b = 0;
    while ( b == 0 ) {
        pthread_mutex_lock(&mutex);
        if ( nbtickets > 0) {
	        nbtickets_vendus++;
	        sched_yield(); /* Do not touch this line */
	        nbtickets--;
        } else {
            b = 1;
        }
        pthread_mutex_unlock(&mutex);
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
    if ( argc >= 2 ) {
	nbtickets = atoi( argv[1] );
    }
    for (int i = 0; i < 8; i++) {
        pthread_create(&threads[i], NULL, vendeur, (void *)(intptr_t)i);
    }
    for (int i = 0; i < POOL; i++) {
        pthread_join(threads[i], &r);
        nbtickets_vendus += (int)(intptr_t)r;
    }
    printf( "%d tickets ont été vendus (nbtickets = %d)\n",
	    nbtickets_vendus, nbtickets );
    
    return EXIT_SUCCESS;
}

