#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define NSITI 200
#define NSTEPS 100000
#define NSTORIE 1000

int inserimento (double siti[]);
void storia (double siti[], double dist[]);

int main () {
  double siti[NSITI] = {0}, dist[NSTEPS] = {0};
  srand48(time(0));

  for (int i=0; i<NSTORIE; i++) { 
    storia(siti, dist);           //simulazione di NSTORIE storie ambientali
  }

  for (int i=1; i<NSTEPS; i++) {
    dist[i] /= NSTORIE;           //calcolo distanza quadratica media ad ogni passo
    printf ("%d %lf\n", i, dist[i]);
    }

  return 9;
}

int inserimento (double siti[]) {
  for (int i=0; i<NSITI; i++) {
    siti[i] = drand48();     //assegno ad ogni sito la probabilità di andare verso sinistra (verso destra è 1-p(sinistra))
  }
  return 0;
}

void storia (double siti[], double dist[]) {
  double k;
  int pos = inserimento(siti);
  for (int i=0; i<NSTEPS; i++) {
    k = drand48();
    if (k < siti[pos+(NSITI/2)]) pos--;
    else pos++;
    dist[i] += pos*pos;
  }
}
