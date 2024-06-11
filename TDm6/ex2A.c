#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define TAILLEBUF 1024

int main(void)
{
    int wv, rv, fd1 = open("./Source.txt", O_RDONLY), fd2 = open("./Destination.txt", O_WRONLY);
    char* buf = (char*) malloc(sizeof(char*) * TAILLEBUF);

    rv = read(fd1, buf, TAILLEBUF);
    while(rv != 0)
    {
        if (rv < 0)
        {
            perror("Erreur : lecture de fichier");
            exit(1);
        }

        wv = 0;
        while(wv < rv)
        {
            wv += write(fd2, buf+wv, rv - wv);
        }

        rv = read(fd1, buf, TAILLEBUF);
    }

    return 0;
}