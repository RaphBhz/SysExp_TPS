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
    
    while(1) {
        /* Tapez CTRL+C pour arrêter. */
        s = litLigne(0);	
        ecrire(1, s);
        ecrire(1, "\n");

        if (s == NULL)
        {
            break;
        }
        free(s);
    }

	return 0;
}

