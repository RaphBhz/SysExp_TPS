#include "gestionProcess.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main()
{
    pid_t pid = fork();

    if (pid == 0)
    {
        sleep(1);
        /* On éxecute le fichier exécutable du source testIB1.c pour recouvrir le processus fils. */
        execl("./testIB1", "./testIB1", (char*) NULL);
    } else if (pid > 0)
    {
        /* On attend que le processus fils finisse avant de compléter l'exécution du processus père. */
        /* Tant que waitpid ne renvoie pas la valeur de l'id du processus fils, celui-ci n'est pas terminé. */
        while (waitpid(pid, NULL, WNOHANG) != pid);
        print_pid_ppid("Je suis le Père");
    } else 
    {
        perror("Erreur : Fork");
        exit(1);
    }

    return 0;
}   