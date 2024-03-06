#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include"utils.h"
#include<stdlib.h>
#include <sys/wait.h>


/*int main() {
    printf("Avant fork, PID = %d\n", getpid());

    if (fork() && (fork() || fork()) ) {
        // Code du processus parent
        printf("Je suis le processus parent, PID = %d\n", getpid());
    } else {
        // Code du processus fils
        printf("Je suis le processus fils, PID = %d\n", getpid());
    }

    printf("Après fork, PID = %d\n", getpid());
*/


  
    
    /*printf("S1");
    fprintf(stderr, "E1");
    if(fork()){
     printf("S2\n");
    }
    else{
      int status;
      wait(&status);
      printf("S3\n");
    }*/
    /*printf("S1");
    fprintf(stderr, "E1");
    printf("S2\n");
    fprintf(stderr, "E2");
    printf("S3");
    exit(0);*/
    //printf("s3\n");
     //printf("S4\n");
    //return 0;
    
/*int main(void){

  int fd[2];
  
  unlink(tubename);
  mkfifo(tubename, 0600);
  if( fork()){
      fonction1(fd[0]);
  }
  else{
      fonction2(fd[1]);
  }
  return EXIT_SUCESS;*/
  



int main(void) {
    int pipe_fd[2];
    pid_t pid;

    // Créer un tube anonyme
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Créer un processus fils
    if ((pid = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Code du processus fils (cd et ls)
        close(pipe_fd[0]); // Fermer l'extrémité de lecture du tube dans le processus fils

        // Rediriger la sortie standard vers l'extrémité d'écriture du tube
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]); // Fermer l'extrémité d'écriture du tube


        execlp("ls", "ls", (char *)NULL);
        perror("execlp ls");
        exit(EXIT_FAILURE);
    } else {
        // Code du processus parent (wc -l)
        close(pipe_fd[1]); // Fermer l'extrémité d'écriture du tube dans le processus parent

        // Rediriger l'entrée standard depuis l'extrémité de lecture du tube
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]); // Fermer l'extrémité de lecture du tube

        // Compter les lignes avec wc -l
        execlp("wc", "wc", "-l", (char *)NULL);
        perror("execlp wc -l");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}






