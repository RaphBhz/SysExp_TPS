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

    /* Le paramètre 0 permet de lire directement les entrées de la console */
	s = litLigne(0);
	
	printf("La première ligne : <%s>\n", s);
	
    if (s == NULL)
    {
        perror("Erreur : lecture du fichier\n");
        exit(1);
    }

	/* Libération de la mémoire allouée et du fichier ouvert dans gestionFichiers */
	free(s);

	return 0;
}

