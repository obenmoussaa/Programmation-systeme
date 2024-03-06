#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "utils.h"


// Gestionnaire de signal personnalisé pour SIGINT
void handle_sigint(int signum) {
    printf("Signal SIGINT reçu. Gestion personnalisée.\n");
}

int main() {
    // Définition du gestionnaire de signal pour SIGINT
    signal(SIGINT, handle_sigint);
    printf("le pid est %d\n", getpid());
    // Simulation d'une attente infinie
    while (1) {
        sleep(1);
        printf("En attente...\n");
    }

    return 0;
}

