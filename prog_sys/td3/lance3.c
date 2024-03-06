#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "utils.h"
#include<string.h>


int main(int argc, char *argv[])
{  

   
    exit_if( argc < 3, "pas assez d'arguments");
    pid_t pid = fork();
    const char *sortie = argv[1];
    const char *command = argv[2];
    int fd_sortie = open(sortie, O_WRONLY | O_CREAT |O_TRUNC,  0644);
  
    if (fd_sortie == -1) {
        perror("Erreur lors de l'ouverture du fichier de sortie");
        return 1;
    }
  int rc = write(fd_sortie, command, strlen(command));
  write(fd_sortie, " ", 1);
  for (int i = 3; i < argc; ++i) {
        write(fd_sortie, argv[i], strlen(argv[i]));
        if (i < argc - 1) {
            write(fd_sortie, " ", 1);
        }
   }
  write(fd_sortie, "\n", 1);
  exit_if( rc == -1 , "erreur");
  char *tab[10];
  int i;
  for (i = 3; i < argc; ++i){
      tab[i - 3] = argv[i];
    }
  tab[i] = NULL; 
  close(fd_sortie);
  // case 0 le fils   dup2(fd_sortie, STDOUT_FILENO);
  execv(command, argv + 2);
  exit_if( rc == -1, "erreur");
  

  return EXIT_SUCCESS ;
}

