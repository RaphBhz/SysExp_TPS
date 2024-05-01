#include "gestionFichiers.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char * argv[])
{
	char * s;
	int fd1, fd2;

	/* On vérifie que l'utilisateur a bien entré deux arguments */
    if (argc != 3)
    {
        printf("Usage: %s <source> <destination>\n", argv[0]);
        exit(1);
    }

	/* Ouverture du fichier de l'argument 1 en lecture */
	fd1 = open(argv[1], O_RDONLY);
	if (fd1 < 0)
	{
		perror("Erreur : Ouverture fichier test");
		exit(1);
	}
	/* Ouverture du fichier de l'argument 2 en écriture */
    fd2 = open(argv[2], O_WRONLY);
	if (fd2 < 0)
	{
		perror("Erreur : Ouverture fichier test");
		exit(1);
	}

	/* Lecture de toutes les lignes du fichier 1 et écriture dans le fichier 2 jusqu'à ce que l'on n'ait plus rien à lire. */
    while(1)
    {
        s = litLigne(fd1);
        if (s == NULL)
        {
            break;
        }
        ecrire(fd2, s);
        free(s);
    }

	/* Libération de la mémoire allouée et du fichier ouvert dans gestionFichiers */
	close(fd1);
	close(fd2);
	free(s);

	return 0;
}

