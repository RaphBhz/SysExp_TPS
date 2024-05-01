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

	fd = open("fichierTest.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Erreur : Ouverture fichier test");
		exit(1);
	}

	s = litLigne(fd);
	
	printf("La première ligne : <%s>\n", s);
	
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

