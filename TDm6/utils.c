int somme1(int **tableau, int n, int m)
{
   int i,j, somme;
   somme = 0;
   for (i=0; i < n; i++) {
      for (j=0; j < m; j++) {
         somme += tableau[i][j];
      }
   }
   return somme;
}

int somme2(int **tableau, int n, int m)
{
   int i,j, somme;
   somme = 0;
   for (j=0; j < m; j++) {
      for (i=0; i < n; i++) {
         somme += tableau[i][j];
      }
   }
   return somme;
}