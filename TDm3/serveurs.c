#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "gestionServeurs.h"

int main()
{
    /* pid : id du processus, fd : descripteur de fichier, tube : tube de communication */
    int pid, fd, tube[2];

    /* On ouvre un pipe dans le processus, si le retour de la fonction est 0, il y a une erreur. */
    if (pipe(tube) != 0)
    {
        perror("Erreur : création du pipe.");
        exit(1);
    }

    /* On dédouble le processus courant. */
    pid = fork();

    /* Dans le processus père, on ouvre le fichier "Source.txt" duquel le contenu doit être communiqué. */
    /* On se permet également de fermer la lecture du tube qui ne lui est pas utile. */
    if (pid > 0)
    {
	    fd = open("Source.txt", O_RDONLY);
        close(tube[0]);
    /* Dans le processus fils, on ouvre le fichier "Destination.txt" dans lequel le contenu doit être acheminé. */
    /* On se permet également de fermer l'écriture du tube qui n'est pas utile ici. */
    } else if (pid == 0)
    {
        fd = open("Destination.txt", O_WRONLY);
        close(tube[1]);
    /* Si le pid est négatif, il y a eu une erreur lors du dédoublement. */
    } else
    {
        perror("Erreur : dédoublement.");
        exit(1);
    }

    /* On vérifie que notre ouverture précédente n'a pas déclenché d'erreur. */
    if (fd < 0)
	{
		perror("Erreur : ouverture fichier test");
		exit(1);
	}

    /* Dans le processus père, on écrit le contenu de notre fichier source dans le tube. */
    if (pid > 0)
    {
        cpy(fd, tube[1]);
    /* Dans le processus fils, on écrit le contenu du tube dans notre fichier destination. */
    } else if (pid == 0)
    {
        cpy(tube[0], fd);
    }

    /* On ferme les entrées du tube restantes. */
    if (pid > 0)
    {
        close(tube[1]);
    } else if (pid == 0)
    {
        close(tube[0]);
    }

    /* On ferme le descripteur de fichier. */
    close(fd);

    return 0;
}