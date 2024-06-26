#include "gestionFichiers.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	char * s;
	int fd;

	/* Ouverture du fichier test */
	fd = open("fichierTest.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Erreur : Ouverture fichier test");
		exit(1);
	}

	/* Test de litLigne */
	s = litLigne(fd);
	printf("La première ligne : %s", s);
	
    if (s == NULL)
    {
        perror("Erreur : lecture du fichier\n");
        exit(1);
    }

	/* Libération de la mémoire allouée et du fichier ouvert dans gestionFichiers */
	close(fd);
	free(s);

	return 0;
}

