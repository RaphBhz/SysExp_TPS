#include "gestionProcess.h"

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    pid_t pid = fork();

    if (pid == 0)
    {
        /* Attention : Si le processus père se termine avant le processus fils,
            le ppid du fils ne pourra plus correspondre au pid du père car ce dernier n'existe plus.
         */
        print_pid_ppid("Fils");
    } else if (pid > 0)
    {
        print_pid_ppid("Père");
    } else 
    {
        perror("Erreur : Fork");
        exit(1);
    }

    return 0;
}