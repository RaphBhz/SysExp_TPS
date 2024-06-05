#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

/* Pour répondre à la problématique de cet exercice, on va créer une sémaphore par thread.
   La sémaphore du premier thread sera initialisée à 1 et les autres à 0.
   Avant chaque impression, on attend que la sémaphore du thread courant soit disponible.
   Après chaque impression, on libère la sémaphore du thread suivant.
   Ainsi, garantit l'ordre d'exécution des impressions de chaque thread les unes après les autres. */

struct ArgT
{
    int i;
    sem_t* sems;
};

void* printThread(void* arg)
{
    struct ArgT* args = (struct ArgT*)arg;
    int j, i = args->i;

    for(j = 0; j < 10; j++)
    {
        if (sem_wait(&(args->sems[i])) < 0)
        {
            perror("Erreur : attente de sémaphore");
            exit(1);
        }
        printf("Affichage %d du thread %d\n", j+1, i+1); /* Thread Pi avec i = 1, 2, 3 */
        
        if (sem_post(&(args->sems[(i + 1) % 3])) < 0)
        {
            perror("Erreur : libération de sémaphore");
            exit(1);
        }
    }

    return NULL;
}

int main(void)
{
    /* tx : id du thread x, args : arguments des threads, sem : sémaphores utilisés par les threads, i : itérateur de création des threads */
    pthread_t tx[3];
    sem_t sems[3];
    struct ArgT args[3];
    args[0].i = 0;
    args[0].sems = sems;
    args[1].i = 1;
    args[1].sems = sems;
    args[2].i = 2;
    args[2].sems = sems;

    /* Initialisation des sémaphores, le 1 est prêt à print. */
    if (sem_init(&sems[0], 0, 1) < 0 ||
        sem_init(&sems[1], 0, 0) < 0 ||
        sem_init(&sems[2], 0, 0) < 0)
    {
        perror("Erreur : initialisation des sémaphores");
        exit(1);
    }

    printf("Lancement des threads...\n");

    /* On créé les threads. */
    if (pthread_create(&tx[0], NULL, printThread, &args[0]) != 0 ||
        pthread_create(&tx[1], NULL, printThread, &args[1]) != 0 ||
        pthread_create(&tx[2], NULL, printThread, &args[2]) != 0)
    {
        perror("Erreur : création de thread");
        exit(1);
    }
    
    /* Attente de la fin de l'exécution des threads créés. */
    pthread_join(tx[0], NULL); 
    pthread_join(tx[1], NULL); 
    pthread_join(tx[2], NULL); 
    
    /* Libération des sémaphores. */    
    if (sem_destroy(&sems[0]) < 0 ||
        sem_destroy(&sems[1]) < 0 ||
        sem_destroy(&sems[2]) < 0)
    {
        perror("Erreur : destruction des sémaphores");
        exit(1);
    }

    printf("Thread exécutés !\n");

    return 0;
}
