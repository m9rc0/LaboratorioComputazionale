#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/*
  In questo programma si utilizza l'algoritmo basato sulle liste, si considerano condizioni al bordo fisse 
 */

/*
  Si utilizza l'algoritmo suggerito dal libro, poi si usa il metodo di bisezione per trovare il valore di pc
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

double findAverage(long int L, double p);

struct siteCluster *cluster;
long int *temp, *neighbour[4];

#include "funzioni.h"

int main(int argc, char *argv[]){
  long int L;
  double p = 0.5, dp = 0.01, epsilon = 0.005, delta = 1, temp = -1, pc;


  if (argc != 2){
    printf("Usage: ./cluster L\n");
    exit(-5);
  }

  L = atoi(argv[1]);
  srand48(time(0));
  
  inizio (L);
  while (fabs(delta) >= epsilon) {       //i valori iniziali di delta e tempdelta sono inizializzati in modo che alla prima iterazione aggiunge dp
    pc = findAverage(L,p);
    delta = pc - 0.5;
    printf ("p = %.10lf, pc = %lf\n", p, pc);
    if ((delta*temp)<0) dp *= (-0.5);
    p += dp;
    temp = delta;
  }

  printf ("Risultato finale: %.3lf\n", p-dp);



  
  return 9;
}

/*********************** FUNZIONI ****************************/


double findAverage(long int L, double p){
  // prende come input la grandezza del reticolo e la probabilità dei guasti, fa 100 simulazioni e ritorna la probabilità di trovare un cluster esteso
  long int nSimul = 1000, i;
  double ris = 0;
  

  for(i = 0; i < nSimul; i++){
    initCluster(L, p);
    findConnections(L);
    ris += (double)findExtended(L);
  }
  ris /= nSimul;
  //  printf("L %lu p %f F %f\n", L, p, ris);
  return ris;
}

/*******************************/
