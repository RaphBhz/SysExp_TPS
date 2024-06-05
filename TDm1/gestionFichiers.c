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
	int nbr, i;
	char* s;
	char* buffer = malloc(sizeof(char) * TAILLEBUF);
	if (buffer == NULL)
	{
		free(buffer);
		return NULL;
	}

	for (nbr = 0; nbr < TAILLEBUF; ++nbr)
	{
		/* On lit la suite du fichier du descrpiteur à l'adresse mémoire du début du buffer + le nombre de char lus. */
		if (read(fd, buffer+nbr, 1) != 1) 
		{
			if (nbr != 0) break;

			free(buffer);
			return NULL;
		}

		/* On s'arrête dès que l'on croise un retour à la ligne. */
		if (buffer[nbr] == '\n')
		{
			break;
		}
	}

	/* Si on est arrivé à cette valeur, la boucle s'est arrêtée car nous avons rempli le buffer, on ne sait donc pas si la ligne a été entièrement lue.
		Commenté car on veut quand même récupérer la valeur dans le TDm4
	if (nbr >= TAILLEBUF - 1)
	{	
		free(buffer);
		return NULL;
	}
	*/

	s = malloc(sizeof(char) * (nbr+1));
	if (s == NULL)
	{
		free(buffer);
		return NULL;
	}

	/* On copie le buffer dans la string */
	for (i = 0; i <= nbr; ++i)
	{
		s[i] = buffer[i];
	}
	free(buffer);

	return s;
}

void ecrire(int fd, char* s)
{
	int rv;
	int taille = strlen(s);
	/* On écrit la string dans le fichier */
	rv = write(fd, s, taille);
	if (rv < 0)
	{
		perror("Erreur : écriture du fichier");
		exit(1);
	}
}
