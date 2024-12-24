#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>   
#include <stdarg.h>

char *reticoloOld, *reticoloNew;
void checkPointer(void *p);
void initReticolo (long int L);
void localUpdate (long int L, long int riga, long int colonna);
void globalUpdate (long int L);

int main (int argc, char *argv[]) {
  long int L, i, j, NUM_ITER;
  FILE *gp, *sD;
  char fileName[100];
  
  if (argc != 3) {
    printf ("Usage: ./nomefile L NUM_ITER\n");
    exit(-1);
  }
  L = (long int)atoi(argv[1]);
  NUM_ITER = (long int)atoi(argv[2]);
  initReticolo(L);

  gp = popen("gnuplot", "w");
  checkPointer(gp);
  fprintf(gp,"set key bottom right\n");  fflush(gp);
  fprintf(gp,"set size ratio -1\n");  fflush(gp);

  for (i = 0; i < NUM_ITER; i++) {
    sprintf(fileName,"scratch.dat%3.3ld",i+1);
    sD = fopen(fileName,"w");
    for (j = 0; j < L*L; j++) {
      if (reticoloOld[j] == 1) {
	fprintf(sD, "%lu %lu\n", j%L, j/L);
      }
    }
    fprintf(gp,"plot [0:%lu][0:%lu] \"%s\" t \" level %ld\"\n",L, L, fileName, i+1);
    fflush(gp);
    fprintf(gp,"pause 0.3 \"level %ld waiting 1\"\n",i+1); fflush(gp);
    fflush(sD);
    fclose(sD);
    globalUpdate(L);
  }
  fprintf(gp,"exit\n");
  fflush(gp);
  
  return 9;
}

/*********************** FUNZIONI ****************************/

void checkPointer(void *p)
{
  if (p == NULL)
    {
      printf("Errore con il puntatore!\n");
      exit(-1);
    } 
}

/****************************/

void initReticolo (long int L) {
  reticoloOld = (char *)calloc(L*L,sizeof(char));
  checkPointer(reticoloOld);
  reticoloNew = (char *)calloc(L*L,sizeof(char));
  checkPointer(reticoloNew);

  //inizializza col pentomino-R
  reticoloOld[L/2 + L*L/2] = reticoloOld[L/2-1 + L*L/2] = reticoloOld[L/2 + L*(L/2-1)] = reticoloOld[L/2 + L*(L/2+1)] = reticoloOld[L/2+1 + L*(L/2+1)] = 1;
  reticoloNew[L/2 + L*L/2] = reticoloNew[L/2-1 + L*L/2] = reticoloNew[L/2 + L*(L/2-1)] = reticoloNew[L/2 + L*(L/2+1)] = reticoloNew[L/2+1 + L*(L/2+1)] = 1;
}

/****************************/

void localUpdate (long int L, long int riga, long int colonna) {
  int count = 0;

  //si conta in senso orario cominciando da in alto a sinistra
  count += reticoloOld[colonna-1 + L*(riga-1)];
  count += reticoloOld[colonna + L*(riga-1)];
  count += reticoloOld[colonna+1 + L*(riga-1)];
  count += reticoloOld[colonna+1 + L*riga];
  count += reticoloOld[colonna+1 + L*(riga+1)];
  count += reticoloOld[colonna + L*(riga+1)];
  count += reticoloOld[colonna-1 + L*(riga+1)];
  count += reticoloOld[colonna-1 + L*riga];

  if ((reticoloOld[colonna + L*riga] == 0) && (count == 3)) {
    reticoloNew[colonna + L*riga] = 1;
  }
  else if ((reticoloOld[colonna + L*riga] == 1) && (count != 2) && (count != 3)) {
    reticoloNew[colonna + L*riga] = 0;
  }
}

/****************************/

void globalUpdate (long int L) {
  long int riga,colonna;

  for (riga = 1; riga < L-1; riga++) {
    for (colonna = 1; colonna < L-1; colonna++) {
      localUpdate(L,riga,colonna);  
    }
  }
  for (riga = 1; riga < L-1; riga++) {
      for (colonna = 1; colonna < L-1; colonna++) {
	reticoloOld[colonna + L*riga] = reticoloNew[colonna + L*riga];
      }
  }
}

/****************************/


