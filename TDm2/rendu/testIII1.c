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
    /* Dédoublement du processus avant l'ouverture du fichier. */
    pid_t pid = fork();

    /* Ouverture du fichier après dédoublement. */
    int fd = open("../TDm1/fichierTest.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("Erreur : Ouverture fichier test");
        exit(1);
    }

    /* Les deux processus vont afficher le même résultat. */
    /* L'ouverture du fichier s'est fait après dédoublement, ainsi, les deux processus ont un file descriptor différent. */
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