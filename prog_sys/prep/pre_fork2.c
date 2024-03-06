#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include "utils.h"


/*écrire un programme qui crée 5 fils en utilisant une boucle for. On remarquera que pour que le fils ne crée pas lui-même plusieurs fils, il faut interompre la boucle par
un break dans le fils*/

int main(void) {
    pid_t pid;
    //int cpt;

   for (int i = 1; i <= 66; ++i) {
   pid = fork();

   switch (pid)
    {
    case -1:
        exit_if(1, "fork");
    case 0:
    
        fprintf(stderr, "Je suis le fils de pid %d\n", getpid());
        exit(EXIT_SUCCESS);
    default:
         
         fprintf(stderr, "Je suis le pere de pid %d\n", getpid());
         waitpid(pid, NULL ,0);
         break;
      }
      }  
  
      //printf("DDSV\n");

    return 0;
}

