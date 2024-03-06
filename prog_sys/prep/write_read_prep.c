#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "utils.h"

#define BUFFER_SIZE 200

int main( int argc, char *argv[] )
{
    char buffer[BUFFER_SIZE];
    ssize_t len_read, wrote, rc;

    while(1){
	len_read = read( STDIN_FILENO, buffer, BUFFER_SIZE );
	exit_if( len_read == -1, "read" );
	if ( len_read == 0 ) {
	    /* EOF*/
	    return EXIT_SUCCESS;
	}

	wrote = 0;
	/*h
	
	 * Si jamais write n'écrit pas assez, on doit boucler pour
	 * tout écrire avant de repasser à read
	 */
	while( wrote < len_read ){
	    rc = write( STDOUT_FILENO, buffer + wrote, len_read - wrote );
	    exit_if( rc == -1, "write" );
	    wrote += rc;
	} 
    }
    return EXIT_SUCCESS;
}
