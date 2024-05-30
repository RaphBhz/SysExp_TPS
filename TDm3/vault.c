/* Nécessaire pour l'utilisation de kill() */
#define _POSIX_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include "../TDm1/gestionFichiers.h"

/*
/// @brief Fonction de prise en charge de signal de fin de décompte du coffre-fort. 
/// @param sig id du signal envoyé.
*/ 
void sleepHandler(int sig)
{
    printf("Trop tard : coffre-fort fermé\n");
    exit(sig);
}

int main()
{
    /* pid : id du processus, s : code lu */
    int pid;
    char* s;

    /* On dédouble le processus courant. */
    pid = fork();

    /* Dans le processus fils, on va compter l'écoulement des 10 secondes. */
    if (pid == 0)
    {
        /* On attends les 10 secondes avant d'envoyer le signal au processus père. */
        sleep(10);

        /* On lève le signal de terminaison du programme. */
        if (kill(getppid(), SIGTERM) == -1)
        {
            perror("Erreur : arrêt du processus fils");
            exit(1);
        }
        exit(0);

    /* Dans le processus père, on ouvre l'entrée standard pour lire le code entré par l'utilisateur. */
    } else if (pid > 0)
    {
        /* Prise en charge  */
        signal(SIGTERM, sleepHandler);
  
        /* On lit une ligne sur l'entrée standard. */
        s = litLigne(0);

        /* Si l'utilisateur a entré un code avant 10 secondes, on annule le compte à rebours. */
        kill(pid, SIGKILL);

        /* On compare le code entré par l'utilisateur à notre mot de passe. */
        if (strcmp(s, "1234\n") == 0)
        {
            printf("Bravo : coffre-fort ouvert\n");
            exit(0);
        } else
        {
            printf("Code faux : coffre-fort fermé\n");
            exit(0);
        }
    /* Si le pid est négatif, il y a eu une erreur lors du dédoublement. */
    } else
    {
        perror("Erreur : dédoublement.");
        exit(1);
    }

    return 0;
}