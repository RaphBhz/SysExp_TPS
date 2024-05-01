#include "gestionFichiers.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    /* Passer la valeur 1 en paramètre permet d'écrire dans la sortie standard. */
    ecrire(1, "J'écris dans la console !!!\n");

	return 0;
}

