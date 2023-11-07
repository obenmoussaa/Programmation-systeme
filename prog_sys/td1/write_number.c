#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <string.h>
#include "utils.h"

int main(int argc, char *argv[])
{
    long number = 5;
    int rc = write(1, &number, sizeof(long)); // fd=1 pour la sortie standard
    exit_if(rc ==-1, "write");    
    rc = write(1, &rc, sizeof(int)); // fd=1 pour la sortie standard
    exit_if(rc ==-1, "write"); 
    return EXIT_SUCCESS;
    
}
