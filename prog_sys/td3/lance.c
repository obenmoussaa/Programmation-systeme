#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "utils.h"
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>


int main(int argc, char *argv[]) {
    int rc;
    const char *sortie = argv[1];
    const char *commande = argv[2];
    int fd_sortie = open(sortie, O_WRONLY | O_CREAT | O_TRUNC, 0644);
   
    if (fd_sortie == -1) {
    
          perror("Erreur lors de l'ouverture du fichier de sortie");
          return 1;
          
    }
    write(fd_sortie, commande, strlen(commande));
    for (int i = 2; i < argc; ++i) {
 	rc = write(fd_sortie, argv[i], strlen(argv[i]));
	exit_if(rc==-1, "error");
	if (i < argc - 1) {
	    rc = write(STDOUT_FILENO, " ", 1);
            exit_if(rc==-1, "error");	    
    }
    rc = write(fd_sortie, "\n", 1);
    exit_if(rc == -1, "error");
    
    pid_t pid = fork();
    if ( pid == -1 ){
    	  perror("Erreur");
          return 1;
    }
    
    else if( pid == 0 ){
	    if (dup2(fd_sortie, STDOUT_FILENO) == -1) {
		perror("Erreur lors de la redirection de la sortie standard");
		return 1;
	    } 
	    rc = execvp(commande, argv + 2);
	    exit_if( rc == -1, "error");
    }
    
    else{   
            close(fd_sortie);
    	    wait(NULL);
    }
    
   
    return 1;
}

