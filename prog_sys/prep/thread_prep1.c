
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "utils.h"
#include <stdint.h>

void *ma_fonction_thread(void *arg)
{
intptr_t resultat;
printf("Je suis un thread. Veuillez entrer un entier\n");
scanf("%ld", &resultat);
pthread_exit( (void*)resultat );
}
int main(void)
{
int ret;
pthread_t my_thread;

ret = pthread_create(&my_thread, NULL,
ma_fonction_thread, (void*)NULL);
if (ret != 0){
fprintf(stderr, "Erreur de cration du thread");
exit (1);
}
pthread_join(my_thread, (void*)&ret); 
printf("Dans le main, ret = %d\n", ret);
return 0;


}
