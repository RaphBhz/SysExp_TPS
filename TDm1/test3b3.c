#include "gestionFichiers.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    char* s;

    /* On lit en continu les entrées de la console et on les réécris dans la console. */    
    /* Tapez CTRL+C pour arrêter. */
    while(1) {
        /* Le paramètre 0 permet de lire directement les entrées de la console */
        s = litLigne(0);	
        ecrire(1, s);

        if (s == NULL)
        {
            break;
        }
        free(s);
    }

	return 0;
}

