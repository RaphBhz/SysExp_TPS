#ifndef _GESTION_FICHIERS_H
#define _GESTION_FICHIERS_H

/*
    @brief Lit dix caractères du fichier dont le descripteur est fd.
    @param  fd Le descripteur du fichier à lire.
    @return Un pointeur vers une chaîne de caractères de dix caractères lus.
*/
char* litDixCaracteres(int);

/*
    @brief Lit une ligne du fichier dont le descripteur est fd.
    @param  fd Le descripteur du fichier à lire.
    @return Un pointeur vers une chaîne de caractères contenant la ligne lue.
*/
char* litLigne(int);

/*
    @brief Écrit la chaîne de caractères s dans le fichier dont le descripteur est fd.
    @param  fd Le descripteur du fichier à écrire.
    @param  s  La chaîne de caractères à écrire.
*/
void ecrire(int, char*);

#endif
