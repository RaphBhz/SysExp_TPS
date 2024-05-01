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
	int fd;

	/* On vérifie que l'utilisateur a bien entré un unique argument */
    if (argc != 2)
    {
        printf("Usage: %s <fichier>\n", argv[0]);
        exit(1);
    }

	/* Ouverture du fichier passé en argument. */
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Erreur : Ouverture fichier test");
		exit(1);
	}

	/* Test de litLigne */
	s = litLigne(fd);
    if (s == NULL)
    {
        perror("Erreur : lecture du fichier\n");
        exit(1);
    }

	printf("La première ligne : %s", s);
	
	/* Libération de la mémoire allouée et du fichier ouvert dans gestionFichiers */
	close(fd);
	free(s);

	return 0;
}

