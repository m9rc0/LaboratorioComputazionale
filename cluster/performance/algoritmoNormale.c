#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

struct siteCluster {
  char spin;
  long int label;
};

/****** VARIABILI GLOBALI ********/
struct siteCluster *cluster;
long int *neighbour[4], *temp;

void checkPointer(void *p);
void initCluster(long int L, double p);
void inizio(long int L);
void initNeighbour(long int L);
long int siteUpdate(long int direction, long int site);
void globalUpdate(long int L);


int main(int argc, char *argv[])
{
  /*
    Questo programma misura l'efficienza dell'algoritmo normale per la ricostruzione di cluster connessi
   */
  clock_t t;
  long int L, nSimul, i, seed;
  double p, timeTaken = 0.;
  // inizializzo il generatore di numeri casuali


  if (argc != 5){
    printf("Usage: ./nomefile L p nSimul seed\n");
    exit(-2);
  }

  L = (long int)atoi(argv[1]);
  p = (double)atof(argv[2]);
  nSimul = (long int)atoi(argv[3]);
  seed = (long int)atoi(argv[4]);
  srand48(seed);
  
  inizio(L);



  for (i = 0; i < nSimul; i++){
    initCluster(L, p);
    t = clock();
    globalUpdate(L);
    timeTaken += (clock() - t);
  }


  timeTaken /= CLOCKS_PER_SEC;
  printf("L = %lu, p = %lf, nSimul = %lu\n", L, p, nSimul);
  printf("Algoritmo normale, tempo necessario in secondi: %lf\n", timeTaken);
  
  return 9;
}

/********** FUNZIONI ***********/


void checkPointer(void *p)
{
  if (p == NULL){
    printf("Errore con il puntatore!\n");
    exit(-1);
  }
}

/*******************************/

void initCluster(long int L, double p){
  long int i, j, a, max = L*L-1, nGuasti;
  nGuasti = (long int)(L*L*p + 0.5);
  // all'inizio sono tutti cluster isolati
  for (i = 0; i < L; i++){
    for (j = 0; j < L; j++){
      cluster[j + L * i].spin = '+';
      cluster[j + L * i].label = j + L * i;
      temp[j + L*i] = j+L*i;
    }
  }

  for (i = nGuasti-1; i >= 0; i--){
    a = (long int)(drand48()*max);
    cluster[temp[a]].spin = '-';
    temp[a] = temp[max];
    max--;
  }

    // per vedere se fatto bene
  /* for (long int i =0; i<L; i++) { */
  /*   for (long int j=0; j<L; j++) { */
  /*     printf ("%c ", cluster[j+i*L].spin); */
  /*   } */
  /*   printf ("\n"); */
  /* } */
}


/*******************************/

void inizio(long int L){
  // libero gli array se precedentemente usati
  free(cluster);
  free(temp);
  for (int i = 0; i < 4; i++){
    free(neighbour[i]);
  }

  cluster = (struct siteCluster *)malloc(L*L*sizeof(struct siteCluster));
  checkPointer(cluster);

  temp = (long int *) malloc(L*L*sizeof(long int));
  checkPointer(temp);

  initNeighbour(L);
}

/*******************************/

void initNeighbour(long int L){
  long int i, j;
  // riserviamo memoria per gli array
  for (i = 0; i < 4; i++){
    neighbour[i] = (long int *) malloc(L*L*sizeof(long int));
    checkPointer(neighbour);
  }

  for (i = 0; i < L; i++){
    for (j = 0; j < L; j++){
      neighbour[UP][j + L*i] = j + L*(i-1);
      neighbour[DOWN][j + L*i] = j + L*(i+1);
      neighbour[LEFT][j + L*i] = (j-1) + L*i;
      neighbour[RIGHT][j + L*i] = (j+1) + L*i;
    }
  }
  // al bordo si punta a sè stessi
  for (i = 0; i < L; i++){
    neighbour[UP][i] = i;
    neighbour[DOWN][i+L*(L-1)] = i+j*(L-1);
    neighbour[LEFT][i*L] = L*i;
    neighbour[RIGHT][L-1 + i*L] = L-1 + L*i;
  }
}

/*******************************/ 

long int siteUpdate(long int direction, long int site){
  char change = 0;
  int n  = neighbour[direction][site];

  if (cluster[site].spin == cluster[n].spin){
    if (cluster[site].label < cluster[n].label){
      change = 1;
      cluster[n].label = cluster[site].label;
    } else if (cluster[site].label > cluster[n].label){
      change = 1;
      cluster[site].label = cluster[n].label;
    }
  }

  return change;
}

/*******************************/

void globalUpdate(long int L){
  long int change = 1, i;

  while (change != 0){
    change = 0;
    for (i = 0; i < L*L; i++){
      change += siteUpdate(RIGHT, i);
      change += siteUpdate(DOWN, i);
      change += siteUpdate(LEFT, i);
      change += siteUpdate(UP, i);
    }
  }
  // per vedere se tutto funziona
  /*   for (long int i =0; i<L; i++) { */
  /*   for (long int j=0; j<L; j++) { */
  /*     printf ("%lu ", cluster[j+i*L].label); */
  /*   } */
  /*   printf ("\n"); */
  /* } */

}
