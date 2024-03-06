#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "sys/wait.h"
#include "utils.h"



void transfere(int fd_in, int fd_out, int buffer_size){
        close(fd_in);
        char buffer[buffer_size];
        ssize_t rc = read(fd_out, buffer, buffer_size);
        exit_if (rc == -1, "read");
        write(STDOUT_FILENO, buffer, rc);
        close(fd_out);
}

int main(int argc, char *argv[])
{
    char  *ls[] = { "ls", "-l", NULL};
    int backup;
    char  *grep[] = { "grep", ".c", NULL};
    char  *wc[] = { "wc", "-l", NULL};
    char **commandes[] = { ls, grep, wc};
    int nb_commandes = sizeof(commandes) / sizeof(char*);
    int tube[2];
    int fd_read;
    int fd_write;
    int rc;
    
    for ( int i=0; i<nb_commandes; i++ ){
	    if ( i < nb_commandes-1 ) {
		exit_if( pipe(tube) == -1, "pipe"); 
	    	fd_read = tube[0];
	    	fd_write = tube[1];
	    	}
    	pid_t pid = fork();
    	switch(pid){
    	case -1: 
    	   exit_if(1, "fork");
    	case 0:
    	    /*entrée*/
    	    if ( i > 0 ){
    	      exit_if(dup2(backup, 0) == -1 , "dup stdin");
    	      close(backup);
    	    }
    	    /*sortie*/
    	    if( i < nb_commandes - 1 ) {
    	    exit_if(dup2(fd_write, 1) == -1 , "dup");
    	    close(fd_write);
    	    close(fd_read);
    	    }
    	    /* exec */
            rc = execvp(commandes[i][0], commandes[i]);
	    exit_if( rc == -1, "error");
            break;
    	
    	default:
    	/* choses à fermer */
    	/* chose à preparer pour l'itération suivante */
    	   if (i > 0 ){
    	    close (backup);
    	   }
    	   if ( i < nb_commandes - 1 ){
    	     close(fd_write);
    	     backup = fd_read;
    	   }
    	   
    	} 
    }  
    /*for(int i=0; i<nb_commandes; i++){
    int wstatus;
    pid_t rpid= waitpid(-1,&wstatus,0);
    exit_if(rpid==-1,"waitpid");
    if(WIFEXITED(wstatus)){
        fprintf(stderr,"my son ");
    }
   }*/
    
    
    return EXIT_SUCCESS;
}
  
