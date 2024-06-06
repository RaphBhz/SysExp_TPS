
#define _XOPEN_SOURCE 500

#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <getopt.h>

#define MAX_FILE 50
#define MAX_RAND 999
#define SIZE_TAB 10

void reset(){
    /* TODO 
    *   shm_unlink();
    *   sem_unlink();
    *   sem_unlink();
    */

    printf("reset\n");

    if (shm_unlink("/tab") < 0 ||
        sem_unlink("/nonVide") < 0 ||
        sem_unlink("/nonPlein") < 0)
    {
        perror("Erreur : libération des sémaphores et de la mémoire");
        exit(1);
    }
}

int* init_sem_mem(sem_t ** nonVide, sem_t **nonPlein){
    /* TODO
     * shm_open()
     * ftruncate()
     * mmap()
     * sem_open()
     * sem_open()
     */

    int* tab;
    int fd = shm_open("/tab", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

    if (fd < 0)
    {
        perror("Erreur : initialisation de la mémoire partagée");
        exit(1);
    }

    if (ftruncate(fd, sizeof(int) * SIZE_TAB) < 0)
    {
        perror("Erreur : découpage du fichier en mémoire");
        exit(1);
    }

    tab = (int*) mmap(NULL, sizeof(int) * SIZE_TAB, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (tab == MAP_FAILED)
    {
        perror("Erreur : mappage mémoire");
        exit(1);
    }

    *nonPlein = sem_open("/nonPlein", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, SIZE_TAB);
    *nonVide = sem_open("/nonVide", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, 0);
    if (*nonVide == SEM_FAILED || *nonPlein == SEM_FAILED)
    {
        perror("Erreur : création des sémaphores");
        exit(1);
    }

    close(fd);
    return tab;
}

void producteur(){
    /* TODO
     * int * tab;
     * sem_t * nonVide;
     * sem_t * nonPlein;
     * init_sem_mem(); => initialise tab, nonVide et nonPlein
     * boucle production
     * munmap()
     */

    int i;
    int* tab;
    sem_t* nonVide, *nonPlein;

    tab = init_sem_mem(&nonVide, &nonPlein);

    for (i = 0; i < MAX_FILE; ++i)
    {
        sem_wait(nonPlein);
        tab[i] = ((random()/(double) RAND_MAX)*MAX_RAND)+1; 
        printf("[+] %d\n", tab[i % SIZE_TAB]);
        sem_post(nonVide);
    }

    if (munmap(tab, sizeof(int) * SIZE_TAB) < 0)
    {
        perror("Erreur : dé-mappage de la mémoire");
        exit(1);
    }

}

void consommateur(){
    /* TODO
     * int * tab;
     * sem_t * nonVide;
     * sem_t * nonPlein;
     * init_sem_mem(); => initialise tab, nonVide et nonPlein
     * boucle consommation
     * munmap()
     */

    int i;
    int* tab;
    sem_t* nonVide, *nonPlein;

    tab = init_sem_mem(&nonVide, &nonPlein);
    for (i = 0; i < MAX_FILE; ++i)
    {
        sem_wait(nonVide);
        printf("tab[%d] = %d\n", i, tab[i % SIZE_TAB]); 
        sem_post(nonPlein);
    }
    
    if (munmap(tab, sizeof(int) * SIZE_TAB) < 0)
    {
        perror("Erreur : dé-mappage de la mémoire");
        exit(1);
    }

}

void usage()
{
    printf("must be run with either one of these option : -reset or -r, -producer or -d, -consumer or -c\n");
}

int main(int argc , char * argv[]){

    static struct option long_options[] =
    {
        {"reset",     no_argument, 0, 'r'},
        {"producer",  no_argument, 0, 'p'},
        {"consumer",  no_argument, 0, 'c'},
        {0, 0, 0, 0}
    };
    /* getopt_long stores the option index here. */
    int option_index = 0;
    int c = getopt_long (argc, argv, "rpc",
            long_options, &option_index);

    /* Initialisation de la fonction random avec une seed unique */
    srandom(time(NULL));

    /* Detect the end of the options. */
    if (c == -1)
        usage();
    else
        switch (c)
        {

            case 'r':
                reset();
                break;

            case 'p':
                producteur();
                break;

            case 'c':
                consommateur();
                break;

            default: break;
        }
    if (optind < argc)
    {
        usage();
        while (optind < argc)
            printf ("%s ", argv[optind++]);
        putchar ('\n');
    }


    return 0;
}
