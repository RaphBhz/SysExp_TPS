#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

void print_pid(char* s)
{
    /* On récupère le pid du processus courant */
    printf("[%d] %s\n", getpid(), s);
}

void print_ppid(char* s)
{
    /* On récupère le pid du processus parent */
    printf("[%d] %s\n", getppid(), s);
}

void print_pid_ppid(char* s)
{
    /* On récupère le pid du processus courant */
    printf("[%d, %d] %s\n", getpid(), getppid(), s);
}