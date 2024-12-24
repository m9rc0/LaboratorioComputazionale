#include <stdio.h>
#include <stdlib.h>
#include <time.h>



#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3


struct siteCluster {
  char spin;
  struct siteCluster *next;
  struct siteCluster *former;
  struct siteCluster *parent;
  struct siteCluster *son;
};


struct siteCluster *cluster;
long int *temp, *neighbour[4];

#include "funzioni.h"

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

  t = clock();

  for (i = 0; i < nSimul; i++){
    initCluster(L, p);
    t = clock();
    findConnections(L);
    timeTaken += (clock() - t);
  }

  timeTaken /= CLOCKS_PER_SEC;
  printf("L = %lu, p = %lf, nSimul = %lu\n", L, p, nSimul);
  printf("Algoritmo con le liste, tempo necessario in secondi: %lf\n", timeTaken);
  
  return 9;
}
