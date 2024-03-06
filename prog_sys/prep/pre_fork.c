#include <unistd.h>
#include <sys/wait.h>
#include "utils.h"
#include<stdio.h>
#include<stdlib.h>
#include <errno.h> /* permet de récupérer les codes d'erreur */



pid_t pid_fils;
int main(void)
{
int a=5;
int status;
switch (pid_fils=fork())
                           {
case -1 : perror("Problème dans fork()\n");
exit(errno); /* retour du code d'erreur */
break;
case 0 : puts("Je suis le fils");
puts("Je retourne le code 3");
a=8;
exit(3);
default : puts("Je suis le père");
puts("Je récupère le code de retour");
wait(&status);
printf("code de sortie du fils %d : %d\n",
pid_fils, WEXITSTATUS(status));
break;

}
printf("%d\n",a);
return 0;
}
