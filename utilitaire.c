// #include "./utilitaire.h"

/*
* UTILITAIRES
*/
void initTab0(int tab[], int dim)
{
  int i;
  for(i = 0; i < dim-1 ; i++)
  {
    tab[i] = 0;
  }
}

void triTab(int tab[], int dim)
{
  int i;
  for(i = 0; i < dim-1 ; i++)
  {
    tab[i] = i;
  }
}

void cloneTab(int tab[], int tabClone[], int dim)
{
  int i;
  for(i=0 ; i < dim; i++)
    tabClone[i] = tab[i];
}

void initMatrice(int ligne, int colonne, float matrice[ligne][colonne])
{
  int i, j;
  for(i = 0; i < ligne ; i++)
    for(j = 0; j < colonne; j++)
      matrice[i][j] = 0;
}

void displayTab(int tab[], int dim)
{
  int i;
  for(i=0 ; i < dim ; i++)
    printf("%d ", tab[i]);
  printf("\n");
}


void randomTab(int tab[], int dim)
{
  int i;
  srand((int) clock());

  for(i = 0; i < dim; i++)
    tab[i] = rand()%(dim + 10);

}

void ordonTab(int tab[], int dim)
{
  int i;
  for(i = 0; i < dim ; i++)
    tab[i] = i;
}

int testTri(int tab[], int dim)
{
  int i = 0, j= 0;
  while (i < dim-1) {
    if(tab[i] > tab[i+1]){
      j++;
    }
    i++;
  }
  return j == 0;
}
