#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//TODO shake sort, bubble sort, bubblesort opti, quicksort

void permute(int *pos1, int *pos2)
{
  int tmp = 0;
  tmp = *pos1;
  *pos1 = *pos2;
  *pos2 = tmp;
}

/*
* TRIS
*/


void insertSort(int tab[], int dim, float *temps)
{
  int i, j;
  clock_t t1, t2;
  t1 = clock();
  for(i = 1 ; i < dim ; i++)
  {
    int itemInsert = tab[i];
    for(j=i ; j > 0 && tab[j-1] > itemInsert ; j--)
      tab[j] = tab[j-1];
    tab[j] = itemInsert;
  }
  t2 = clock();
  *temps = (float)(t2-t1) / (CLOCKS_PER_SEC);
}

void selectionTri(int tab[], int dim, float *temps)
{
  int k = dim, pmax = 0, j;
  clock_t t1, t2;
  t1 = clock();

  for(k = 0; k < dim-1; k++)
  {
    pmax = k;
    for(j= k+1; j<dim ; j++ )
    {
      if(tab[j] < tab[pmax])
        pmax = j;
    }
    permute(&tab[pmax], &tab[k]);
  }

  t2 = clock();
  *temps = (float)(t2-t1) / (CLOCKS_PER_SEC);
}

void echangeTri(int tab[], int dim, float *temps)
{
  int k, i;
  clock_t t1, t2;
  t1 = clock();
  for(k = dim-1; k >= 0; k--)
  {
    for(i = 0 ; i < k+1 ; i++)
    {
      if(tab[i] > tab[i+1]){
        permute(&tab[i], &tab[i+1]);
      }
    }
  }
  t2 = clock();
  *temps = (float)(t2-t1) / (CLOCKS_PER_SEC);
}


void bubbleSortOpt(int tab[], int dim, float *temps)
{
  int i, dimR = dim, test;

  clock_t t1, t2;
  t1 = clock();

  while (dimR > 1) {
    test = 1;
    for(i = 0; i < (dimR-1) ; i++){
        if(tab[i] > tab[i+1] ){
            permute(&tab[i], &tab[i+1]);
            test = 0;
        }
      }
      if(test == 1)
        break;
      dimR--;
    }

    t2 = clock();
    *temps = (float)(t2-t1) / (CLOCKS_PER_SEC);
}

void shakeSort(int tab[], int dim, float *temps)
{
  clock_t t1, t2;
  t1 = clock();
  int i ;
  int booleenTableauTrie = 0 ;
  int debut = 0 ;
  int fin = dim - 1 ;

  while (!booleenTableauTrie)
  {
      booleenTableauTrie = 1 ;

      for ( i = debut ; i < fin ; i++)
          if (tab[i+1] < tab[i])
          {
              permute(&tab[i], &tab[i+1]);
              booleenTableauTrie = 0 ;
          }

      fin-- ;

      for ( i = fin ; i > debut ; i--)
          if (tab[i] < tab[i-1])
          {
              permute(&tab[i], &tab[i-1]);
              booleenTableauTrie = 0 ;
          }

      debut++ ;

  }
    t2 = clock();
    *temps = (float)(t2-t1) / (CLOCKS_PER_SEC);
}



void shellSort(int tab[], int dim, float *temps)
{
  int i , j , iteration, tmp ;
  int k = 0 ;
  int pas = 3;
  clock_t t1, t2 ;


  while ( k < dim/2)
      k = pas * k + 1;

  k/=pas ;

  t1 = clock() ;

  do
  {
      for ( iteration = 0 ; iteration < k; iteration++)

          for ( i = iteration + k ; i < dim; i+=k)
          {
              j = i - k ;
              tmp = tab[i];

              while( j >= iteration && tmp < tab[j] )
              {
                  tab[j+k] = tab[j];
                  j-=k;
              }

              tab[j+k] = tmp ;

          }
      k/= pas ;
  }

  while (k > 0);
  t2 = clock();
  *temps = (float)(t2-t1) / (CLOCKS_PER_SEC);
}

void placer(int g, int d, int *T)
{
  int i, j, x, place_trouvee;
  x = T[g];                     /* x est la valeur à placer */
  i = g;                        /* i est la position provisoire de x */
  j = 2*g+1;                    /* j est l'indice de son premier fils */
  place_trouvee = 0;

  while((j<=d) && !(place_trouvee))
  {
    if(j<d)
      if(T[j+1]>T[j]) j = j+1;
                                /* T[j] est alors le plus grand des fils */
    if(x>=T[j])
      place_trouvee = 1;
    else
    {
      T[i] = T[j];            /* le plus grand des fils "remonte" */
      i = j;                  /* et la place provisoire de x "descend" */
      j = 2*i+1;
    }
  }
  T[i] = x;                   /* i est la position définitive de x */
}

void heapSort(int tab[], int dim, float *temps)
{
  int i;
  clock_t t1, t2;
  t1 = clock();
  for(i = dim/2 ; i >= 0 ; i--)
    placer(i, dim-1, tab);

  for(i= dim-1 ; i >=1 ; i--)
  {
    int temp = tab[0];
    tab[0] = tab[i];
    tab[i] = temp;
    placer(0, i-1, tab);
  }
  t2 = clock();
  *temps = (float)(t2-t1) / (CLOCKS_PER_SEC);

}


int partitionner(int tabqs[], int premier, int dernier)
{
  int p = tabqs[premier];
  int i = premier - 1;
  int j = dernier + 1;
  for(;;)
  {
    do {
      i++;
    } while(tabqs[i] < p);
    do {
      j--;
    } while(tabqs[j] > p);

    if (i >= j)
      return j;
    permute(&tabqs[i], &tabqs[j]);
  }
}

void quickSort(int tabqs[], int gauche, int droite)
{
  int p;
  if(gauche < droite)
  {
    p = partitionner(tabqs, gauche, droite);
    quickSort(tabqs, gauche, p);
    quickSort(tabqs, p+1, droite);
  }
}

void quickSortW(int tabqs[], int dim, float *temps)
{
  int prem = 0, der = dim;
  clock_t t1, t2;
  t1 = clock();
  quickSort(tabqs, prem, der);

  t2 = clock();
  *temps = (float)(t2-t1) / (CLOCKS_PER_SEC);
}
