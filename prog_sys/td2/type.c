#include <sys/stat.h>
#include <stdint.h>
#include <stdio.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    struct stat file_info;

    // Obtenir les informations sur le fichier en entrée standard
    if (fstat(STDIN_FILENO, &file_info) == -1) {
        perror("Erreur lors de l'obtention des informations sur le fichier");
        return 1;
    }

    // Afficher les informations
    printf("File type: ");
    switch (file_info.st_mode & S_IFMT) {
        case S_IFBLK:  printf("block device\n");        break;
        case S_IFCHR:  printf("character device\n");    break;
        case S_IFDIR:  printf("directory\n");           break;
        case S_IFIFO:  printf("FIFO/pipe\n");           break;
        case S_IFLNK:  printf("symlink\n");             break;
        case S_IFREG:  printf("regular file\n");        break;
        case S_IFSOCK: printf("socket\n");              break;
        default:       printf("unknown?\n");            break;
    }

    return 0;
}
