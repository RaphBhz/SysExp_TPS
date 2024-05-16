#include "../TDm1/gestionFichiers.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main()
{
    char* s;
    int fd;
    pid_t pid;

    /* Ouverture du fichier avant dédoublement. */
    fd = open("../TDm1/fichierTest.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("Erreur : Ouverture fichier test");
        exit(1);

    }

    /* Dédoublement du processus après ouverture du fichier. */
    /* Les deux processus ont un output différent. Les caractères sont comme alternés. */
    /* Comme l'ouverture de fichier s'est faite avant le dédoublement, les deux processus ont un file descriptor similaire. */
    /* Les deux processus se partagent donc les accès au fichier. */
    pid = fork();
    if (pid == 0)
    {
        s = litLigne(fd);
        if (s == NULL)
        {
            perror("Erreur : Lecture fichier test");
            exit(1);
        }
        printf("Lecture fils : %s\n", s);
    } else if (pid > 0)
    {
        s = litLigne(fd);
        if (s == NULL)
        {
            perror("Erreur : Lecture fichier test");
            exit(1);
        }
        
        /* Temporisation du processus fils pour clarifier l'output. */
        while (waitpid(pid, NULL, WNOHANG) != pid);
        printf("Lecture père : %s\n", s);
    } else 
    {
        perror("Erreur : Fork");
        exit(1);
    }

	close(fd);
	free(s);
    return 0;
}   