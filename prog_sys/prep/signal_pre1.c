/*Dans cet exemple, le programme configure un gestionnaire de signal pour SIGUSR1 et utilise sigsuspend pour attendre la réception de ce signal tout en masquant tous les autres signaux. Une fois que SIGUSR1 est reçu, le masque de signaux est restauré à sa valeur précédente.*/



#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handle_signal(int signum) {
    printf("Signal %d reçu.\n", signum);
}

int main() {
    // Configuration d'un gestionnaire de signal pour SIGUSR1
    struct sigaction sa;
    sa.sa_handler = handle_signal;
    sa.sa_flags = 0;
    sigaction(SIGUSR1, &sa, NULL);

    // Masquage de tous les signaux sauf SIGUSR1 pendant l'attente
    sigset_t mask, prev_mask;
    sigfillset(&mask);
    sigdelset(&mask, SIGUSR1);

    // Mémoriser le masque de signaux actuel
    sigprocmask(SIG_SETMASK, &mask, &prev_mask);

    printf("En attente de SIGUSR1...\n");

    // Utilisation de sigsuspend pour attendre SIGUSR1
    sigsuspend(&mask);

    // À ce stade, SIGUSR1 a été reçu

    printf("Réveillé par SIGUSR1. Restauration du masque de signaux.\n");

    // Restaurer le masque de signaux précédent
    sigprocmask(SIG_SETMASK, &prev_mask, NULL);

    return 0;
}

