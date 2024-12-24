#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/*
  Questo programma genera cammini aleatori in 3 dimensioni, con la caratteristica di essere autoevitanti: ogni sito che è già stato visitato una volta non potrà più essere visitato
 */

#define MEMORY_STEP 10000

struct x{
  long int x1;
  long int x2;
  long int x3;
};

void checkPointer(void *p);
struct x *extendTraiettoria(struct x *traiettoria, int n);
struct x nextStep(struct x pos, struct x traiettoria[], long int time);
int checkPosition(struct x pos, struct x traiettoria[], long int time);
int checkEnd(struct x pos, struct x traiettoria[], long int time);
struct x initPos();
long int runSimulation(struct x *traiettoria);


int main(){
  struct x *traiettoria = NULL;
  long int t = 0;
  int nSimul = 100, i;

  srand48(time(0));
  
  
  for (i = 0; i < nSimul; i++){
    t += runSimulation(traiettoria);
  }

  printf("Numero simulazioni = %i\n", nSimul);
  printf("Tempo medio per fermarsi = %lf\n" , (double)t/nSimul);
  
  return 9;
}

/************************* FUNZIONI **************************/

/***************************************************/

void checkPointer(void *p)
{
  if (p == NULL)
    {
      printf("Errore con il puntatore!\n");
      exit(-1);
    }
  
}

/***************************************************/

struct x *extendTraiettoria(struct x *traiettoria, int n){

  traiettoria  = realloc(traiettoria, n*MEMORY_STEP*(sizeof(struct x)));
  checkPointer(traiettoria);
  return traiettoria;
} 

/***************************************************/

struct x nextStep(struct x pos, struct x traiettoria[], long int time){
  double randomNumber;

  // si muove per forza in qualche direzione
  
  randomNumber = drand48();

  do {
    if (randomNumber < 1./6.){
      pos.x1++;
    } else if (randomNumber < 2./6.){
      pos.x1--;
    } else if (randomNumber < 3./6.){
      pos.x2++;
    } else if (randomNumber < 4./6.){
      pos.x2--;
    } else if (randomNumber < 5./6.){
      pos.x3++;
    } else {
      pos.x3--;
    }
  } while (checkPosition(pos, traiettoria, time) == 1);
   
    return pos;
}

/***************************************************/

int checkPosition(struct x pos, struct x traiettoria[], long int time){
  long int i;
  // ritorna 0 se la posizione non è già stata occupata, ritorna 1 altrimenti
  
  for (i = 0; i < time; i++){
    if ((traiettoria[i].x1 == pos.x1) && (traiettoria[i].x2 == pos.x2) && (traiettoria[i].x3 == pos.x3)) return 1;
  }

  return 0;
}

/***************************************************/

int checkEnd(struct x pos, struct x traiettoria[], long int time){
  int myFlag = 0;
  struct x temp;
  // ritorna 0 se ci sono vicini liberi, 1 altrimenti

  
  temp = pos;
  temp.x1++;
  myFlag = checkPosition(temp, traiettoria, time);

  if (myFlag == 0){
    return myFlag;
  }

  temp = pos;
  temp.x1--;
  myFlag = checkPosition(temp, traiettoria, time);

  if (myFlag == 0){
    return myFlag;
  }

  temp = pos;
  temp.x2++;
  myFlag = checkPosition(temp, traiettoria, time);

  if (myFlag == 0){
    return myFlag;
  }

  temp = pos;
  temp.x2--;
  myFlag = checkPosition(temp, traiettoria, time);

  if (myFlag == 0){
    return myFlag;
  }

  temp = pos;
  temp.x3++;
  myFlag = checkPosition(temp, traiettoria, time);

  if (myFlag == 0){
    return myFlag;
  }

  temp = pos;
  temp.x3--;
  myFlag = checkPosition(temp, traiettoria, time);

  return myFlag;

}

/***************************************************/

struct x initPos(){
  // inizializza all'origine
  struct x pos = {0};
  return pos;
}

/***************************************************/

long int runSimulation(struct x *traiettoria){
  long int t = 1;
  int myFlag = 0;

  traiettoria = malloc(MEMORY_STEP * sizeof(struct x));
  checkPointer(traiettoria);

  traiettoria[0] = initPos();

  while (myFlag == 0){
    traiettoria[t] = nextStep(traiettoria[t-1], traiettoria, t);
    myFlag = checkEnd(traiettoria[t-1], traiettoria, t);
    t++;
    if ((t % MEMORY_STEP) == 0){
      traiettoria = extendTraiettoria(traiettoria, t/MEMORY_STEP + 1);
    }    
  }
 
  free(traiettoria);
  return t;
}

/***************************************************/
