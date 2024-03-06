#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>

int aleatoire();

void f();
void g();

int main(int argc, char *argv[])
{
    srand(time(NULL)); // initialisation aléatoire
    signal(SIGALRM, f);
    signal(SIGUSR1, g);

    int temps_attente = aleatoire();
    printf("Temps d'attente : %d secondes\n", temps_attente);
    alarm(temps_attente);

    sleep(aleatoire());

    kill(getpid(), SIGUSR1);

    return 0;
}

int aleatoire()
{
    float max = 3.0;
    int nombre = (int)(max * rand() / RAND_MAX);
    return nombre;
}

void f()
{
    printf("Signal SIGALRM reçu. (A)\n");
    exit(EXIT_SUCCESS);
}

void g()
{
    printf("Signal SIGUSR1 reçu. (S)\n");
    exit(EXIT_SUCCESS);
}

