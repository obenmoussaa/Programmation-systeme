#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include"utils.h"




pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;
void* ma_fonction_thread(void *arg);
int main(void)
{
	int i;
	pthread_t thread[10];
	srand(time(NULL));
	for (i=0 ; i<10 ; i++)
	pthread_create(&thread[i], NULL, ma_fonction_thread, (void*)i);
	for (i=0 ; i<10 ; i++)
	pthread_join(thread[i], NULL);
	return 0;
}

void* ma_fonction_thread(void *arg)
{
	int num_thread = (int)arg;
	int nombre_iterations, i, j, k, n;
	nombre_iterations = rand()%8;
	for (i=0 ; i<nombre_iterations ; i++)
	{
	n = rand()%10000;
	pthread_mutex_lock(&my_mutex);
	printf("Le thread numro %d commence son calcul\(\backslash\)n", num_thread);
	for (j=0 ; j<n ; j++)
	for (k=0 ; k<n ; k++)
	{}
	printf("Le thread numero %d a fini son calcul\(\backslash\)n", num_thread);
	pthread_mutex_unlock(&my_mutex);
	}
	pthread_exit(NULL);
}
