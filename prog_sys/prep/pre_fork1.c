#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include"utils.h"
#include"sys/wait.h"

/*crire un programme qui crée deux fils appelés fils 1 et fils 2. Le père doit
afficher “je suis le père” et le fils 1 doit afficher “je suis le fils 1”, et le fils 2 doit afficher “je
suis le fils 2”.*/



int main(int argc, char* argv[]) {
    
    pid_t pid1, pid2;
    switch (pid1 = fork())
    {
    case -1:
        exit_if(1, "fork");
    case 0:
        fprintf(stderr, "Je suis le fils 1 de pid %d\n", getpid());
        break;
    default:
          waitpid(pid1, NULL ,0);
       
         fprintf(stderr, "Je suis le pere de pid %d\n", getpid());
         
         switch (pid2 = fork()){
          case -1:
              exit_if(1, "fork2");
          case 0:
              fprintf(stderr, "Je suis le fils 2 de pid %d\n", getpid());
          break;
          default:
             waitpid(pid1, NULL ,0);
              waitpid(pid2, NULL ,0);
             fprintf(stderr, "Je suis toujours  le pere de pid %d\n", getpid());
          break;
        
         }}
         printf("chaqchaq\n");
         
    return EXIT_SUCCESS;


}

