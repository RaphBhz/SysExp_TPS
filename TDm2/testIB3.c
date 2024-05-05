#include "gestionProcess.h"

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();

    if (pid == 0)
    {
        sleep(1);
        print_pid_ppid("Fils");
    } else if (pid > 0)
    {
        /* On attend que le processus fils finisse avant de compléter l'exécution du processus père. */
        /* Tant que waitpid ne renvoie pas la valeur de l'id du processus fils, celui-ci n'est pas terminé. */
        while (waitpid(pid, NULL, WNOHANG) != pid);
        print_pid_ppid("Père");
    } else 
    {
        perror("Erreur : Fork");
        exit(1);
    }

    return 0;
}