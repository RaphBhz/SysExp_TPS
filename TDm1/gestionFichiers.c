#include "gestionFichiers.h"

#include <string.h>
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
			perror("Erreur : lecture du fichier");
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

char* litLigne(int fd) {
	const int TAILLEBUF = 1000000;
	int nbr, i;
	char* s;
	char c[1];
	char* buffer = malloc(sizeof(char) * TAILLEBUF);
	if (buffer == NULL)
	{
		free(buffer);
		return NULL;
	}

	for (nbr = 0; nbr < TAILLEBUF; ++nbr)
	{
		if (read(fd, c, 1) != 1) 
		{
			free(buffer);
			return NULL;
		}

		if (*c == '\n')
		{
			break;
		}

		buffer[nbr] = *c;
	}

	if (nbr >= TAILLEBUF - 1)
	{	
		free(buffer);
		return NULL;
	}

	s = malloc(sizeof(char) * (nbr));
	if (s == NULL)
	{
		free(buffer);
		return NULL;
	}

	for (i = 0; i < nbr; ++i)
	{
		s[i] = buffer[i];
	}
	s[nbr] = '\0';
	free(buffer);

	return s;
}

void ecrire(int fd, char* s)
{
	int rv;
	int taille = strlen(s);
	rv = write(fd, s, taille);
	if (rv < 0)
	{
		perror("Erreur : écriture du fichier");
		exit(1);
	}
}
