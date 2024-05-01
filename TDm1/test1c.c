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

	s = litDixCaracteres(fd);
	printf("Les dix premiers caractères: <%s>\n", s);
	
	/* Libération de la mémoire allouée et du fichier ouvert dans gestionFichiers */
	close(fd);
	free(s);

	return 0;
}

