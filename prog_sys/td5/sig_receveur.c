#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include"utils.h"

#define bf_size 128
void * mmap_ptr = NULL;


void gestionnaire(int sig){
	printf("j'ai recu le message\n");
	int rc = write(STDOUT_FILENO, mmap_ptr, 128);
	exit_if( rc == -1, "write");
}

int main() {



     
    
     
    int rc;
    // Afficher le PID du processus
    printf("PID du processus : %d\n", getpid());

    // Définir le gestionnaire de signal pour SIGUSR1
    struct sigaction sa;
    struct sigaction old;
    //initialisation de sa
    if (sigaction(SIGUSR1, NULL, &sa) == -1) { // le 3 eme paramètre c'est le dernier gestionnaire de signal
        perror("Erreur de configuration ");
        return 1;
    }
    sa.sa_handler = sigusr1_handler;  
    if (sigaction(SIGUSR1, &sa, &old) == -1) { // le 3 eme paramètre c'est le dernier gestionnaire de signal
        perror("Erreur de configuration ");
        return 1;
    }

    

    sigset_t sigset;
    rc=sigfillset(&sigset); // pour enregister tous les signals
    exit_if(rc==-1, "sigfillset");
    rc=sigdelset(&sigset, SIGUSR1); //supprimer le signal qui nous intéresse qui est SIGUSR1
    exit_if(rc==-1, "sigdelset");
   
    // Attendre indéfiniment pour permettre au processus de recevoir des signaux
    sigsuspend(&sigset);
    exit_if(sigaction(SIGUSR1,&old,NULL)==-1,"SIGATION");

    return 0;
}
//for ((i=1; i<=500; i++)); do echo -n 'A'; done > majid.txt



  //sa.sa_flags = 0;
