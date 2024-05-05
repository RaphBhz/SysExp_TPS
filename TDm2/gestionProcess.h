#ifndef _GESTION_PROCESS_H
#define _GESTION_PROCESS_H

/*
@brief Affiche la chaîne de caractères passée en paramètre précédée du numéro de processus.
@param s La chaîne de caractères à passer en paramètre.
*/
void print_pid(char*);

/*
@brief Affiche la chaîne de caractères passée en paramètre précédée du numéro de processus parent.
@param s La chaîne de caractères à passer en paramètre.
*/
void print_ppid(char*);

/*
@brief Affiche la chaîne de caractères passée en paramètre précédée des numéros de processus courant et du processus parent.
@param s La chaîne de caractères à passer en paramètre.
*/
void print_pid_ppid(char*);

#endif
