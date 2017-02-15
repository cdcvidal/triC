#include <stdio.h>
#include <string.h>
#include "./tris.c"
#include "./utilitaire.c"

#define NBTRIS 7
#define N 10000
static int tab[N];
static int tabOrd[N];

int tabInstruction[6] = {500,1000,10000,500,1000,10000};

void (* listeFonctions[NBTRIS])(int *,int, float*) = {insertionTri,selectionTri,bubbleSortOpt,shakeSort,shellSort,heapSort,quickSortW};

void (* trouveFonction(int tri))(int *,int, float*)
{
  return listeFonctions[tri];
}

void lanceRandomTris(int tri, int dim, int passage, float *temps)
{
  int i = 0;
  float temp = 0;
  int tabClone[N];
  void (* triDemande)(int *,int, float*);
  triDemande = trouveFonction(tri);
  while(i < passage-1){
    cloneTab(tab, tabClone, dim);
    triDemande(tabClone, dim, temps);
    printf("numero tri = %d test tri %d\n", tri, testTri(tabClone, dim));
    temp += *temps;
    i++;
  }
  *temps = temp/10;
}

void lanceOrdonTris(int tri, int dim, float *temps)
{
  void (* triDemande)(int *,int, float*);
  triDemande = trouveFonction(tri);
  ordonTab(tabOrd, dim);
  triDemande(tabOrd, dim, temps);
}

void lanceTris(int ligne, int colonne, float tabResultats[ligne][colonne])
{
  /*
  * tri par insertion = 0
  * tri par selection = 1
  * tri par échange = 2
  * Shake sort = 3
  * Shell sort = 4
  * Heap sort = 5
  * Quick sort = 6
  */
  int i= 0;
  randomTab(tab, N);

  while(i < NBTRIS)
  {
    lanceOrdonTris(i, tabInstruction[0], &tabResultats[i][0]);
    lanceOrdonTris(i, tabInstruction[1], &tabResultats[i][1]);
    lanceOrdonTris(i, tabInstruction[2], &tabResultats[i][2]);

    lanceRandomTris(i, tabInstruction[0], 10,&tabResultats[i][3]);
    lanceRandomTris(i, tabInstruction[1], 10,&tabResultats[i][4]);
    lanceRandomTris(i, tabInstruction[2], 10,&tabResultats[i][5]);
    i++;
  }
}

void lanceTri(int ligne, int colonne, float tabResultats[ligne][colonne], int num){
  randomTab(tab, N);

  lanceOrdonTris(num, tabInstruction[0], &tabResultats[num][0]);
  lanceOrdonTris(num, tabInstruction[1], &tabResultats[num][1]);
  lanceOrdonTris(num, tabInstruction[2], &tabResultats[num][2]);

  lanceRandomTris(num, tabInstruction[0], 10,&tabResultats[num][3]);
  lanceRandomTris(num, tabInstruction[1], 10,&tabResultats[num][4]);
  lanceRandomTris(num, tabInstruction[2], 10,&tabResultats[num][5]);

}

void header(){
    printf("                                 -------------------------------------------------------------------------------------------\n");

    printf("                                 |                                             |                 Tableaux                  |\n");
    printf("                                 |             Tableaux déjà triés             |         aléatoirement désordonnés         |\n");
    printf("                                 |                                             |         (moyenne sur 10 Tableaux)         |\n");

}

void tableauComparatif(int num )
{
  int ligne = 8, colonne = 7, i, j;
  float tabResultats[7][6];
  initMatrice(7,6, tabResultats);

  if(num < 0)
    lanceTris(7,6,tabResultats);
  else
    lanceTri(7,6,tabResultats, num);

  char colonneGauche[7][50] = {
    "| Tri par insertion | O(n2)      |",
    "| Tri par sélection | O(n2)      |",
    "| Tri par échange   | O(n2)      |",
    "| Shake sort        | O(n2)      |",
    "| Shell sort        | O(n1.2)    |",
    "| Heap sort         | O(n log n) |",
    "| Quick sort        | O(n log n) |"
  };
  header();
  for(i = 0 ; i < ligne ; i++)
  {
    if(i == 0)
      printf("                                 -------------------------------------------------------------------------------------------\n");
    else
      printf("----------------------------------------------------------------------------------------------------------------------------\n");
    for(j = 0 ; j < colonne ; j++)
    {
      if(i == 0){
        if(j == 0)
          printf("                                 ");
        if(j == 1)
          printf("|   %d elts   |",tabInstruction[j-1] );
        if(j > 1)
          printf("  %d elts   |",tabInstruction[j-1] );
      } else {
        if(j == 0){
          printf("%s",colonneGauche[i-1] );
        }
        if(j > 0){
          printf("   %f   |", tabResultats[i-1][j-1]);
        }
      }

    }
    printf("\n");
  }
  printf("----------------------------------------------------------------------------------------------------------------------------\n");
}

int main(void) {
  int request = 0;

  do {

    printf("Que voulez vous tester ?\n (0 = Tableau comparatif )\n (1 = Tri par insertion)\n (2 = Tri par sélection)\n (3 = Tri par échange)\n (4 = Shake sort)\n (5 = Shell sort)\n (6 = Heap sort)\n (7 = Quick sort)\n (9 = Quitter)\n");
    scanf("%d", &request);

    switch (request) {
      case 0:
        printf("\nTableau comparatif\n");
        tableauComparatif(-1);
        break;
      case 1:
        printf("tri 1\n");
        tableauComparatif(0);
        break;
      case 2:
        printf("tri 2\n");
        tableauComparatif(1);
        break;
      case 3:
        printf("tri 3\n");
        tableauComparatif(2);
        break;
      case 4:
        printf("tri 4\n");
        tableauComparatif(3);
        break;
      case 5:
        printf("tri 5\n");
        tableauComparatif(4);
        break;
      case 6:
        printf("tri 6\n");
        tableauComparatif(5);
        break;
      case 7:
        printf("tri 7\n");
        tableauComparatif(6);
        break;
      case 9:
        printf("Le programme a quitter.\n");
        break;
      default:
          printf("Le choix demandé %d n'est pas référencé.\n\n", request);
    }

  } while(request != 9);

  return 0;
}
