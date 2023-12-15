#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include<sys/mman.h>
#include "utils.h"

int main(int argc, char *argv[])
{   
    int rc;
    int *p;
    p = mmap(NULL, sizeof(int), PROT, MAP_PRIVATE |  MAP_ANONYMOUS, -1, 0);
    exit_if( p == MAP_FAILED, "FAILED MMAP");
    fprintf(stderr,"p= %p\n", p);
    fprintf(stderr,"*p= %p\n", *p);
    *p = 42;
    fprintf(stderr,"*p= %p\n", *p);
    rc = munmap(p, sizeof(int));
    exit_if(rc == -1, "mmap");
    return EXIT_SUCCESS;
}

