#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include "utils.h"
#include <sys/stat.h>





int main(int argc, char *argv[])
{   
    struct  nopad np = {.c1='a', .l=4 , .c2='b'};
    ssize_t r = write(1, &np, sizeof(struct nopad));
    //printf("%\nld\n", sizeof(struct nopad));
    exit_if(r == -1, "write"); 
    return EXIT_SUCCESS;
}

