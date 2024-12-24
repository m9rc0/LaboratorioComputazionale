#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define L 20
#define RHO 0.6
#define NPART RHO*L

struct part{
  long int x;
  long int y;
};

void inserimento (long int **reticolo, struct part *posiniz, struct part *posretic, struct part *posass);
void neighbor (long int *plus, long int *minus);

int main () {
  long int **reticolo, *plus, *minus;
  struct part *posiniz, *posretic, *posass;
  srand48(time(0));

  reticolo = (long int**) malloc(L * sizeof(long int *));
  for (int i=0; i<L; i++) reticolo[i] = (long int*) malloc (L * sizeof(long int));
  
  posiniz = (struct part*) malloc(NPART * sizeof(struct part));
  posretic = (struct part*) malloc (NPART * sizeof(struct part));
  posass = (struct part*) malloc (NPART * sizeof (struct part));
  plus = (long int*) malloc (L * sizeof(long int));
  minus = (long int*) malloc(L * sizeof(long int));

  neighbor(plus, minus);

  inserimento (reticolo, posiniz, posretic, posass);

  

  return 9;
}

/***********************************************************************/

void inserimento (long int **reticolo, struct part posiniz[], struct part posretic[], struct part posass[]) {
  long int a,b;
  int ok; 
  for (int i=0; i<L; i++) {
    for (int j=0; j<L; j++) {
      reticolo[i][j] = -1;       //-1 indica che i siti sono vuoti
    }
  }

  for (int i=0; i<NPART; i++) {
    ok = 0;
    do {
      a = (int) (drand48()*L);
      b = (int) (drand48()*L);
      if (reticolo[a][b] == -1) {
	reticolo[a][b] = i;              //+1 indica che il sito è occupato
	posiniz[i].x = posretic[i].x = posass[i].x = a;
	posiniz[i].y = posretic[i].y = posass[i].y = b;
	ok = 1;
      }
    } while (ok == 0);
  }

}

/******************************************************************/

void neighbor (long int *plus, long int *minus) {
  for (int i=0; i<L; i++) {
    plus[i] = i+1;
    minus[i] = i-1;
  }
  plus[L-1] = 0;
  minus[0] = L-1;
}
