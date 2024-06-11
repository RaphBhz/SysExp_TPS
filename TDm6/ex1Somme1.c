#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    int j = 0, i = 0, n = 4096, m = 4096;
    int** t = (int**) malloc(sizeof(int*) * n);

    for (; i < n; ++i)
    {
        t[i] = (int*) malloc(sizeof(int) * m);

        for (j = 0; j < n; ++j)
        {
            t[i][j] = i + j;
        }
    }

    printf("Somme 1 : %d\n", somme1(t, n, m));

    for (i = 0; i < n; ++i)
    {
        free(t[i]);
    }

    free(t);
    return 0;
}