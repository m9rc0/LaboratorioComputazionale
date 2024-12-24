#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MY_EMPTY -1
#define DIM 2
#define INTCONTROLLO 10

void checkPointer(void *p);
long int inizio(long int L, double rho, long int totalTime);
void neighbour (long int *plus, long int *minus, long int L);
void inserimento (long int L, long int NPART);
void dtUpdate (long int part, long int L);
void macroUpdate (long int L, long int nPart, long int iterazioni);
double measure (long int nPart, long int T);
void myEnd (long int totalTime, long int nSimul);

/*** VARIABILI GLOBALI ***/
long int *reticolo, *pos, *posTrue, *posZero, *plus, *minus, *temp;
double *diff;


int main(int argc, char *argv[])
{
  long int L, nPart, totalTime, iterazioni, nSimul = 100, i,j;
  double rho, coeff;

  if (argc != 5)
    {
      printf("Usage: ./gas L rho coeff totalTime\n");
      exit(-6);
    }

  L = atoi(argv[1]);
  rho = atof(argv[2]);
  coeff = atof(argv[3]);
  totalTime = atof(argv[4]);

  
  srand48(time(0));  
  nPart = inizio(L, rho, totalTime);
  iterazioni = (long int)(nPart * coeff);

  for (j = 0; j < nSimul; j++) {
    inserimento(L, nPart);
    for (i = 1; i <= totalTime; i++) {
      macroUpdate (L, nPart, iterazioni);
      if (i % INTCONTROLLO == 0) diff[i / INTCONTROLLO - 1] += measure(nPart, i);
    }
  }
  myEnd (totalTime, nSimul);
  
  return 9;
}

void checkPointer(void *p)
{
  if (p == NULL)
    {
      printf("Errore con il puntatore!\n");
      exit(-1);
    }
  
}


/********************* FUNZIONI ********************/

void inserimento (long int L, long int NPART) {
  long int a, max = L*L-1;
  
  for (int i=0; i<L; i++) {
    for (int j=0; j<L; j++) {
      reticolo[i + L * j] = MY_EMPTY;
      temp[i + L*j] = i + L*j;
    }
  }

  for (long int i = NPART-1; i >= 0; i--)
    {
      a = (long int)(drand48()*max);
      //      printf("%ld, %ld\n", a, max);
      // posizione x
      pos[2*i] = posZero[2*i] = posTrue[2*i] = temp[a] % L;
      // posizione y
      pos[2*i+1] = posZero[2*i+1] = posTrue[2*i+1] = (long int) temp[a] /  L;

      reticolo[temp[a]] = i;
      
      temp[a] = temp[max];

      max--;
    }

  // per vedere se funziona
  for (long int i = 0; i < L; i++)
    {
      printf("|");
      for (long int j = 0; j < L; j++)
	{
	  printf("%ld|", reticolo[i+j*L]);
	}
      printf("\n");
    }
}

/******************************************************************/

void neighbour (long int *plus, long int *minus, long int L) {
  for (int i=0; i<L; i++) {
    plus[i] = i+1;
    minus[i] = i-1;
  }
  plus[L-1] = 0;
  minus[0] = L-1;
}


/*********************/

long int inizio(long int L, double rho, long int totalTime)  
{
  // inizializziamo tutti gli array
  long int nPart;
  nPart = (int) (L * L * rho + 0.5);
  
  reticolo = (long int *) malloc(L * L * sizeof(long int));
  checkPointer(reticolo);

  pos = (long int *)malloc(nPart * DIM * sizeof(long int));
  checkPointer(pos);

  posTrue = (long int *)malloc(nPart * DIM * sizeof(long int));
  checkPointer(posTrue);

  posZero = (long int *)malloc(nPart * DIM * sizeof(long int));
  checkPointer(posZero);

  plus = (long int *)malloc(L * sizeof(long int));
  checkPointer(plus);

  minus = (long int *)malloc(L * sizeof(long int));
  checkPointer(minus);

  neighbour(plus, minus, L);

  diff = (double *) calloc((int) (totalTime / INTCONTROLLO), sizeof(double));
  checkPointer(diff);

  temp = (long int *)malloc(L * L * sizeof(long int));
  checkPointer(temp);

    return nPart;
}

/*********************/

void dtUpdate (long int part, long int L) {
  int direz = (int) (drand48()*4);
  long int nx, ny;

  //le direzioni degli spostamenti sono associate a 0,1,2,3 partendo dallo spostamento verso sinistra e procedendo in senso orario
  
  if (direz == 0) {
    nx = minus[pos[2*part]];
    ny = pos[2*part + 1];
  }
  else if (direz == 1) {
    nx = pos[2*part];
    ny = plus[pos[2*part + 1]];
  }
  else if (direz == 2) {
    nx = plus[pos[2*part]];
    ny = pos[2*part + 1];
  }
  else {
    nx = pos[2*part];
    ny = minus[pos[2*part + 1]];
  }

  if (reticolo[nx + L * ny] == MY_EMPTY) {
    reticolo[nx + L * ny] = reticolo[pos[2*part] + L * pos[2*part + 1]];
    reticolo[pos[2*part] + L * pos[2*part + 1]] = MY_EMPTY;
    pos[2*part] = nx;
    pos[2*part + 1] = ny;
    if (direz == 0) {
      posTrue[2*part]--;
    }
    else if (direz == 1) {
      posTrue[2*part + 1]++;
    }
    else if (direz == 2) {
      posTrue[2*part]++;
    }
    else {
      posTrue[2*part + 1]--;
    }   
  }
}

/*********************/

void macroUpdate (long int L, long int nPart, long int iterazioni) {
  long int a;
  
  for (long int i = 0; i < iterazioni; i++) {
    a = (long int) (drand48() * nPart);
    dtUpdate(a, L);
  }
}

/*********************/

double measure (long int nPart, long int T) {
  long int R2 = 0;
  double d, avR2;

  for (long int i = 0; i < nPart; i++) {
    R2 += (posTrue[2*i] - posZero[2*i]) * (posTrue[2*i] - posZero[2*i]) + (posTrue[2*i + 1] - posZero[2*i + 1]) * (posTrue[2*i + 1] - posZero[2*i + 1]); 
  }
  avR2 = (long double) R2 / (long double) nPart;
  
  d = avR2 / (2 * DIM * T);
  return d;
}

/*********************/

void myEnd (long int totalTime, long int nSimul) {
  long int N = totalTime / INTCONTROLLO;
  
  for (long int i = 1; i <= N; i++) {
    diff[i-1] /= (double) nSimul;
    printf ("%ld %lf\n", i * INTCONTROLLO, diff[i-1]);
  }
}

/*********************/
