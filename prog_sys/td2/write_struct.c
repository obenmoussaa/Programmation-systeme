#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include "utils.h"
#include <sys/stat.h>




int main(int argc, char *argv[])
{   
    struct nopad np;
    ssize_t byte = read(0, &np, sizeof(np));
    exit_if(byte == -1, "Error");
    //printf("%ld\n", sizeof(np)); 
    printf("%c %ld %c" , np.c1, np.l, np.c2);
    return EXIT_SUCCESS;
}

