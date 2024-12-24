#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>



/*
  In questo programma si utilizza l'algoritmo basato sulle liste, si considerano condizioni al bordo fisse 
 */

/*
  Si utilizza l'algoritmo suggerito dal libro 
 */

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

int main(int argc, char *argv[]){
  long int L, i, Lmin, Lmax, dL, nSimul;
  double p, ris, pMin, pMax, dp;


  if (argc != 8){
    printf("Usage: ./cluster Lmin Lmax dL pMin pMax dp nSimul");
    exit(-5);
  }

  Lmin = (long int)atoi(argv[1]);
  Lmax = (long int)atoi(argv[2]);
  dL = (long int)atoi(argv[3]);
  pMin = (double)atof(argv[4]);
  pMax = (double)atof(argv[5]);
  dp = (double)atof(argv[6]);
  nSimul = (long int)atoi(argv[7]);
  
  srand48(time(0));


  for (L = Lmin; L <= Lmax; L += dL){
    for (p = pMin; p <= pMax; p += dp){
      ris = 0;
      inizio (L);
      for(i = 0; i < nSimul; i++){
	initCluster(L, p);
	findConnections(L);
	ris += (double) findExtended(L);
      }
      ris /= nSimul;
      printf("L %lu p %f F %f\n", L, p, ris);
    }
  }


  
  return 9;
}

/*********************** FUNZIONI ****************************/

