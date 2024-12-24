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

long int findSizes(long int L, double **istogramma, long int *length);
long int findDimension(struct siteCluster *genitore);
long int checkIfExtended(struct siteCluster sito, long int L);
double estensioneMedia(double istogramma[], long int histLength);

struct siteCluster *cluster;
long int *temp, *neighbour[4];

#include "funzioni.h"

int main(int argc, char *argv[]){
  long int L, histLength = 0, nCluster = 0, nSimul = 50, i;
  double p, nClusterMedio, *istogramma = NULL, dp = 0.005;

  if(argc != 2){
    printf("Usage: ./nomefile L\n");
    exit(-5);
  }
  L = atoi(argv[1]);
  srand48(time(0));
  inizio (L);
 

  for(p = 0.5; p <= 0.69; p += dp){
    nCluster = 0;
    // rinormalizzo a 0 l'array degli istogrammi
    for(i = 0; i < histLength; i++){
      istogramma[i] = 0;
    }
    for (i = 0; i < nSimul; i++){
      initCluster(L, p);
      findConnections(L);
      nCluster = findSizes(L, &istogramma, &histLength);
    }
    // rinormalizzo le medie
    nClusterMedio = (double)nCluster/nSimul;
    for (i = 0; i < histLength; i++){
      istogramma[i] /= (nSimul*nClusterMedio);
    }
    printf("%lf %lf\n", p, estensioneMedia(istogramma, histLength));
  }


  
  
  return 9;
}

/*********************** FUNZIONI ****************************/

long int findSizes(long int L, double **istogramma, long int *length){
  long int i, j, n = 0, flag, sizeEtichette = 50, sizeCluster, oldLength = *length;
  struct siteCluster **etichette;
  // questa funzione aggiorna l'array delle occorrenze delle dimensioni dei cluster

  etichette = (struct siteCluster **) malloc(sizeEtichette * sizeof(struct siteCluster *));

  
  for (i = 0; i < L*L; i++){
    flag = 0;
    for (j = 0; j < n; j++){
      // controllo che il sito non appartenga a un cluster già inserito
      if (cluster[i].parent == etichette[j]){
	flag++;
      }
    }
    if ((flag == 0)&&(cluster[i].spin == '-')&&(checkIfExtended(cluster[i], L) == 0)){
      n++;
      //       printf("%lu\n", n);
      if (sizeEtichette < n){
	// nel caso ingrandisco l'array delle etichette
	sizeEtichette += 50;
	etichette = (struct siteCluster **)realloc(etichette, sizeEtichette * sizeof(struct siteCluster *));
	checkPointer(etichette);
      }
      etichette[n-1] = cluster[i].parent;
      sizeCluster = findDimension(cluster[i].parent);
      //      printf("%lu\n", sizeCluster);
      
      if ((*length) <= sizeCluster)
	{
	  // se l'array era troppo corto aggiungo della memoria e inizializzo a zero tutti i nuovi membri
	  (*length) = sizeCluster+1;
	  *istogramma = (double *)realloc(*istogramma, (*length) * sizeof(double));
	  for (j = oldLength; j < (*length); j++){
	    (*istogramma)[j] = 0;
	  }
	}
      // aggiorno l'array
      (*istogramma)[sizeCluster]++;
    } 
  }

  
  free(etichette);
  return n;
}

/*******************************/

long int findDimension(struct siteCluster *genitore){
  long int size = 1;
  struct siteCluster *scratch;
  scratch = genitore;
  while (scratch->next != scratch){
    size++;
    scratch = scratch->next;
      }
  return size;
}

/*******************************/

long int checkIfExtended(struct siteCluster sito, long int L){
  long int i, j;
  
  for (i = 0; i < L; i++){
    if (cluster[i].parent == sito.parent){
      // se il parent sta nel bordo di sopra controllo se sta anche sotto, sennò vado avanti
      for (j = 0; j < L; j++){
	if (cluster[j+L*(L-1)].parent == sito.parent){
	  //	  printf("Trovato!\n");
	  return 1;
	}
      }
    }
  }
  return 0;
}

/*******************************/

double estensioneMedia(double istogramma[], long int histLength){
  double S1 = 0, S2 = 0;
  long int i;
  // calcola l'estensione media dei cluster
  for (i = 0; i < histLength; i++){
    S1 += i*i*istogramma[i];
    S2 += i*istogramma[i];
  }
  return S1/S2;
}

/*******************************/


