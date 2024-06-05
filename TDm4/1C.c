#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "../TDm1/gestionFichiers.h"

void* readThread(void* s)
{
    /* Ouverture du fichier Source en lecture. */
    int fd = open("Source.txt", O_RDONLY);

    /* Erreur d'ouverture de fichier. */
    if (fd < 0)
	{
		perror("Erreur : ouverture fichier test");
		exit(1);
	}

    /* On itère jusqu'à ce que le fichier soit totalement lu. */
    while(1)
    {
        /* Lecture d'une ligne du fichier Source. */
        s = litLigne(fd);

        if (s == NULL)
        {
            break;
        }

        printf("Ligne lue : %s", (char*)s);
    }

    /* Fermeture du fichier Source. */
    close(fd);
    return s;
}

void* writeThread(void* s)
{
    /* Ouverture du fichier Destination en écriture. */
    int i, fd = open("Destination.txt", O_WRONLY);

    /* Erreur d'ouverture de fichier. */
    if (fd < 0)
	{
		perror("Erreur : ouverture fichier test");
		exit(1);
	}

    /* On itère jusqu'à ce que le fichier soit totalement lu. */
    /* On implémente une sécurité car la stratégie actuelle peut provoquer une boucle infinie. */
    i = 0; 
    while(1)
    {
        if (i >= 10 || s == NULL)
        {
            break;
        }

        /* Ecriture d'une ligne dans le ficheir Destination. */
        ecrire(fd, s);
        printf("Ligne écrite : %s", (char*)s);
        ++i;
    }

    /* Fermeture du fichier Source. */
    close(fd);
    return NULL;
}

int main(void)
{
    /* tx : id du thread x, s : chaîne de caractères allouée dynamiquement et passée en tant que buffer aux threads. */
    pthread_t t1, t2;
    char* s = malloc(sizeof(char) * TAILLEBUF);

    printf("Lancement des threads...\n");

    /* On créé les threads de lecture et d'écriture des données. */
    if (pthread_create(&t1, NULL, readThread, s) != 0 || pthread_create(&t2, NULL, writeThread, s) != 0)
    {
        perror("Erreur : création de thread");
        exit(1);
    }
    
    /* Attente de la fin de l'exécution des deux threads créés. */
    pthread_join(t1, NULL); 
    pthread_join(t2, NULL); 
    printf("Thread exécutés !\n");
    
    /* On libère la mémoire de la chaîne de caractères. */
    free(s);

    return 0;
}
