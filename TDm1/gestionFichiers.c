#include "gestionFichiers.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

char* litDixCaracteres(int fd)
{
	int nbr, rv;
	char* s = malloc(sizeof(char)*11);
	if (s==NULL)
	{
		perror("Erreur : allocation de la chaîne");
		exit(1);
	}

	for (nbr = 0; nbr < 10;)
	{
		rv = read(fd, s, 10-nbr);
		
		/* Erreur */
		if (rv < 0) {
			perror("Erreur: lecture du fichier");
			exit(1);
		}

		/* Fin du fichier */
		if (rv == 0) break;
		
		nbr += rv;
	}

	/* On doit fermer la string pour emêcher un segmentation fault */
	s[nbr] = '\0';

	return s;
}

