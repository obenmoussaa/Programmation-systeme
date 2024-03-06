#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "sys/wait.h"
#include "utils.h"


int main(){
	printf("debut");
	execlp("echo","echo", "milieu", NULL);
	printf("d");
	return 0;

}
