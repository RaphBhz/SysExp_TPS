#include "../TDm1/gestionFichiers.h"
#include <string.h>
#include <stdlib.h>

void cpy(int fd1, int fd2)
{
    char* buf;

    while(1)
    {
        buf = litLigne(fd1);
        if (buf == NULL) break;
        
        ecrire(fd2, buf);
        
        free(buf);
    }
}