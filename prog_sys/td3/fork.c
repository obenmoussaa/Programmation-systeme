#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/wait.h>
#include "utils.h"

int main(int argc, char *argv[])
{  
  printf("pid du pere %d\n", getpid());
  pid_t fils = fork();  
  if ( fils == -1 ){
    perror("fork problem");
    exit(EXIT_FAILURE);
  } 
  else if ( fils == 0) {
  
    printf("pid du fils %d, pid du pere %d", getpid(), getppid());
    exit(0);
  }
  else{
   wait(NULL);
  }
  return EXIT_SUCCESS;
}
