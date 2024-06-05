#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <string.h>
#include "../TDm1/gestionFichiers.h"

struct ArgT {
    char* s;
    sem_t sem_read;
    sem_t sem_write;
};

void* readThread(void* arg)
{
    /* Buffer de lecture du fichier. */
    char* buffer;

    /* Reconstruction des arguments du thread. */
    struct ArgT* data = (struct ArgT*) arg;

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
        buffer = litLigne(fd);

        /* Si on ne lit plus rien, alors c'est qu'on a atteint la fin du fichier. */
        /* On met EOF pour signaler la fin de la lecture au thread d'écriture. */
        if (buffer == NULL)
        {
            data->s[0] = EOF;
            sem_post(&data->sem_write);
            break;
        }

        /* On attend le dévérouillage de la sémaphore pour accéder à la chaîne de caractères. */
        printf("    readThread attend...\n");
        if (sem_wait(&data->sem_read) < 0)
        {
            perror("Erreur : attente de la sémaphore");
            exit(1);
        }
        strncpy(data->s, buffer, TAILLEBUF);

        /* Libération de la sémaphore. */
        free(buffer);
        sem_post(&data->sem_write);
    }

    /* Fermeture du fichier Source. */
    close(fd);
    return NULL;
}

void* writeThread(void* arg)
{
    /* Reconstruction des arguments du thread. */
    struct ArgT* data = (struct ArgT*) arg;

    /* Ouverture du fichier Destination en écriture. */
    int fd = open("Destination.txt", O_WRONLY);

    /* Erreur d'ouverture de fichier. */
    if (fd < 0)
	{
		perror("Erreur : ouverture fichier test");
		exit(1);
	}

    /* On itère jusqu'à ce que le fichier soit totalement lu. */
    while(1)
    {
        /* On attend le dévérouillage de la sémaphore pour accéder à la chaîne de caractères. */
        printf("    writeThread attend...\n");
        if (sem_wait(&data->sem_write) < 0)
        {
            perror("Erreur : attente de la sémaphore");
            exit(1);
        }

        /* Si le thread de lecture envoie EOF, c'est que la lecture a atteint la fin du fichier */
        if (data->s[0] == EOF)
        {
            break;
        }

        /* Ecriture d'une ligne dans le ficheir Destination. */
        ecrire(fd, data->s);
        
        /* Libération de la sémaphore. */
        sem_post(&data->sem_read);
    }

    /* Fermeture du fichier Source. */
    close(fd);
    return NULL;
}

int main(void)
{
    /* argT : arguments passés au thread contenant la chaîne de caractères et la sémaphore, tx : id du thread x */
    struct ArgT argT;
    pthread_t t1, t2;

    /* Initialisation de la sémaphore */
    sem_init(&argT.sem_read, 0, 1);
    sem_init(&argT.sem_write, 0, 0);
    argT.s = malloc(sizeof(char) * TAILLEBUF);

    printf("Lancement des threads...\n");

    /* On créé les threads de lecture et d'écriture des données. */
    if (pthread_create(&t1, NULL, readThread, &argT) != 0 || pthread_create(&t2, NULL, writeThread, &argT) != 0)
    {
        perror("Erreur : création de thread");
        exit(1);
    }
    
    /* Attente de la fin de l'exécution des deux threads créés. */
    pthread_join(t1, NULL); 
    pthread_join(t2, NULL); 
    printf("Thread exécutés !\n");

    /* Libération des sémaphores. */    
    sem_destroy(&argT.sem_read);
    sem_destroy(&argT.sem_write);

    /* On libère la mémoire allouée pour argT */
    free(argT.s);

    return 0;
}
