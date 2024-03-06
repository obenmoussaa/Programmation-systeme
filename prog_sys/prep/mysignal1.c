#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sigusr1_handler(int signo) {
    printf("Signal reçu : %d\n", signo);
}

int main() {
    // Affiche le PID du processus
    printf("PID du processus : %d\n", getpid());

    // Configuration du gestionnaire pour SIGUSR1
    struct sigaction sa;
    sa.sa_handler = sigusr1_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);

    // En attente d'un sig
    printf("En attente d'un signal...\n");

    // Mettre en place une boucle while pour rester en attente
    while (1) {
        sigset_t mask;
        sigfillset(&mask);
        sigdelset(&mask, SIGUSR1);

        // Suspend le processus jusqu'à ce qu'un signal soit reçu
        sigsuspend(&mask);
    }
    //
    signal(SIGUSR1, SIG_DFL);

    return 0;
}

