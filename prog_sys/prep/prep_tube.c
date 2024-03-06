#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include"utils.h"
#include <sys/wait.h>
#define BUFFER_SIZE 256
int main(void)
{
pid_t pid_fils;
int tube[2];
unsigned char bufferR[256], bufferW[256];
bufferW[0] = 'a';

puts("Cration d'un tube");
if (pipe(tube) != 0) 
{
fprintf(stderr, "Erreur dans pipe\n");
exit(1);
}
pid_fils = fork(); 
if (pid_fils == -1)
{
fprintf(stderr, "Erreur dans fork\n");
exit(1);
}
if (pid_fils == 0) {/* processus fils */

printf("Fermeture entre dans le fils (pid = %d)\n", getpid());
close(tube[1]);
read(tube[0], bufferR, BUFFER_SIZE);
printf("Le fils (%d) a lu : %s\n", getpid(), bufferR);

}
else {
printf("Fermeture sortie dans le pre (pid = %d)\n", getpid());
close(tube[0]);
printf("Message du pre (%d) au fils", getpid());
write(tube[1], bufferW, BUFFER_SIZE);
wait(NULL);
}
return 0;
}
