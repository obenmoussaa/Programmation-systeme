#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include"utils.h"
#define MAX_CLIENTS 10
#define SE_FAIRE_SERVIR 2

int nbclients = 0;
int boucher_libre = 1;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* client(void* arg) {
    int client_id = *(int*)arg;

    pthread_mutex_lock(&mutex); // Acquérir le verrou

    if (nbclients == MAX_CLIENTS) {
        printf("Client %d : Trop de monde, on reviendra plus tard.\n", client_id);
        pthread_mutex_unlock(&mutex); // Libérer le verrou
        return NULL;
    }

    nbclients++;
    printf("Client %d : Arrivé, nombre de clients : %d\n", client_id, nbclients);

    pthread_mutex_unlock(&mutex); // Libérer le verrou

    while (1) {
        pthread_mutex_lock(&mutex); // Acquérir le verrou

        if (boucher_libre) {
            boucher_libre = 0;
            pthread_mutex_unlock(&mutex); // Libérer le verrou
            break; // Sortir de la boucle
        }

        pthread_mutex_unlock(&mutex); // Libérer le verrou
        printf("Client %d : Attente dans la file d'attente.\n", client_id);
        sleep(1); // Attendre un moment avant de réessayer
    }

    printf("Client %d : En train de se faire servir.\n", client_id);
    sleep(SE_FAIRE_SERVIR);

    pthread_mutex_lock(&mutex); // Acquérir le verrou
    boucher_libre = 1;
    nbclients--;
    printf("Client %d : Service terminé, nombre de clients : %d\n", client_id, nbclients);
    pthread_mutex_unlock(&mutex); // Libérer le verrou

    return NULL;
}

int main() {
    pthread_t threads[MAX_CLIENTS];
    int client_ids[MAX_CLIENTS];

    for (int i = 0; i < MAX_CLIENTS; i++) {
        client_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, client, &client_ids[i]);
    }

    for (int i = 0; i < MAX_CLIENTS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

