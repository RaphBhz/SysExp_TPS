#include "../TDm1/gestionFichiers.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

/* Le comportement est identique à celui du programme précédent. */
int main(int argc, char * argv[])
{
    char* s;
    int fd;
    pid_t pid;

	/* On vérifie que l'utilisateur a bien entré deux arguments */
    if (argc != 2)
    {
        printf("Usage: %s <fichier>\n", argv[0]);
        exit(1);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("Erreur : Ouverture fichier test");
        exit(1);

    }

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

	/* Libération de la mémoire allouée et du fichier ouvert dans gestionFichiers */
	close(fd);
	free(s);

	return 0;
}

