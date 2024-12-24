#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NUM_ITER 200

#define L (2*NUM_ITER)

typedef char tipo;

tipo returnState(tipo C[], int index, unsigned int regola);
void updateState(tipo C[], tipo CP[], unsigned int regola);

int main(int argc, char *argv[]){
  tipo C[L] = {0}, CP[L] = {0};
  unsigned int regola, i, j;

  if (argc != 2)
    {
      printf("Usage: ./nomefile regola\n");
      exit(-1);
    }
  regola = (unsigned int)atoi(argv[1]);
  C[(int)(L/2)] = 1;
  printf("# regola: %u\n", regola);
  printf("0 0\n");
  for (i = 1; i <= NUM_ITER; i++){
    updateState(C, CP, regola);
    for (j = 0; j < L; j++){
      //      printf("%i\n", C[j]);
      if (C[j] == 1){
	printf("%i %u\n", j-(int)(L/2), i);
      }
    }
  }
  
  return 9;
}

/*********** FUNZIONI **********/

tipo returnState(tipo C[], int index, unsigned int regola)
{
  unsigned int stato, maschera;
  tipo next;
  stato = 4*C[index-1] + 2*C[index] + C[index+1];
  maschera = pow(2, stato);
  next = (maschera & regola) >> stato;
  //  printf("%i\n", next);
  return next;
}
/***************************************************/

void updateState(tipo C[], tipo CP[], unsigned int regola){
  int i;
  for (i = 1; i < L-1; i++){
    CP[i] = returnState(C, i, regola);
    // alla prossima iterazine i-1 divente i-2 e quindi lo possiamo già cambiare
    C[i-1] = CP[i-1];
  }
  // l'unico che non è stato cambiato
  C[L-2] = CP[L-2];
}

/***************************************************/
