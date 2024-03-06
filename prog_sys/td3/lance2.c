#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "utils.h"


void gen_segfault()
{
	*((int*)0) = 42;
}


int main(int argc, char *argv[])
{
    int rc, i, fd;
    char *cmd,*sortie;
    pid_t pid;
    //chec the number of arg
    exit_if(argc<3, "arguments");
    sortie = argv[1];
    cmd = argv[2];

    //open and create if needed the output file 
    fd = open(sortie,O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    exit_if(fd == -1, "open");

    //write command and args in out put file
    for (i =1;i<argc;i++){
        rc = write(fd, argv[i], strlen( argv[i]));
        exit_if(rc==-1,"write");
        rc = write(fd,"\n",1);
        exit_if(rc==-1,"write");
    }


    pid=fork();
    switch (pid)
    {
    case -1:
        exit_if(1, "fork");
    case 0:
        exit_if(dup2(fd, STDOUT_FILENO)==-1, "dup2");
        close(fd);
        gen_segfault();
        rc=execvp(cmd, argv+2);
        
        exit_if(rc==-1, "execvp");
        break;
    default:
        int wstatus;
        pid_t rpid;
        close(fd);
        rpid = waitpid(pid,&wstatus,0);
        exit_if(rpid == -1, "waitpid");
        if(WIFEXITED(wstatus)) {
            printf("exited, status=%d\n", WEXITSTATUS(wstatus));
        } else if(WIFSIGNALED(wstatus)) {
            printf("killed by signal %d\n", WTERMSIG(wstatus));
        }
        break;
    }
    return EXIT_SUCCESS;
}

