#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "utils.h"


#define CHAINE1 "hello"
#define CHAINE2 "world"





int main(int argc, char *argv[]){

int rc;
 #if defined(UTILISER_FPRINTF1)
 #if defined(UTILISER_SORTIE_ERRUER1)
 	fprintf(stderr, "%s", CHAINE1);
 #else
	fprintf(stdout, "%s", CHAINE1);
 #endif
 #else
	rc = write(STDOUT_FILENO, CHAINE1, strlen(CHAINE1));
	exit_if(rc == -1, "erreur");
 #endif
	sleep(3);
 #if defined(UTILISER_FPRITNF2)
 #if defined(UTILISER_SORTIE_ERREUR2)
	fprintf(stderr, "%s", CHIANE2);
 #else
	fprintf(stdout, "%s", CHAINE2);
 #endif
 #else
	write(STDOUT_FILENO, CHAINE2, strlen(CHAINE2));
	exit_if(rc == -1, "erreur");
 #endif
 #if defined(UTILISER_EXIT)
   	exit(0);
 #else
	_exit(0);
 #endif
 
 
}
